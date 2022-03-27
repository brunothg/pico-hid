/*
* pico-hid - Raspberry Pi Pico HID-Device
* Copyright (C) 2022  Marvin Bruns
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "App.h"

#include <cstdio>
#include <tusb.h>
#include <bsp/board.h>

#include "util/AppConfig.h"
#include "hardware/Button.h"
#include "tusb_descriptors.h"

namespace brunothg_pico_hid {

    extern "C" {
//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// 0=umount, 1=mount, 2=suspend_wakeup_en
    int tud_status_flag = 0;

// Invoked when device is mounted
    void tud_mount_cb(void) {
        tud_status_flag = 1;
    }

// Invoked when device is unmounted
    void tud_umount_cb(void) {
        tud_status_flag = 0;
    }

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
    void tud_suspend_cb(bool remote_wakeup_en) {
        tud_status_flag = (remote_wakeup_en) ? 2 : 0;
    }

// Invoked when usb bus is resumed
    void tud_resume_cb(void) {
        tud_status_flag = 1;
    }

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

    static void send_hid_report(uint8_t report_id, uint32_t btn) {
        // skip if hid is not ready yet
        if (!tud_hid_ready()) return;

        switch (report_id) {
            case REPORT_ID_KEYBOARD: {
                // use to avoid send multiple consecutive zero report for keyboard
                static bool has_keyboard_key = false;

                if (btn) {
                    uint8_t keycode[6] = {0};
                    keycode[0] = HID_KEY_A;

                    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
                    has_keyboard_key = true;
                } else {
                    // send empty key report if previously has key pressed
                    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, nullptr);
                    has_keyboard_key = false;
                }
            }
                break;

            case REPORT_ID_MOUSE: {
                int8_t const delta = 5;

                // no button, right + down, no scroll, no pan
                tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, delta, delta, 0, 0);
            }
                break;

            default:
                break;
        }
    }

    Button btn(AppConfig::PIN_BTN_KEYBOARD);
    Led led(AppConfig::PIN_LED_KEYBOARD);

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
    void hid_task(void) {
        // Poll every 10ms
        const uint32_t interval_ms = 10;
        static uint32_t start_ms = 0;

        if (board_millis() - start_ms < interval_ms) return; // not enough time
        start_ms += interval_ms;

        // Remote wakeup
        if (tud_suspended() && tud_status_flag == 2) {
            // Wake up host if we are in suspend mode
            // and REMOTE_WAKEUP feature is enabled by host
            tud_remote_wakeup();
        } else {
            // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
            send_hid_report(REPORT_ID_KEYBOARD, btn.isPressed());
        }
    }

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
    void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint8_t len) {
        (void) instance;
        (void) len;

        uint8_t next_report_id = report[0] + 1;

        if (next_report_id < REPORT_ID_COUNT) {
            send_hid_report(next_report_id, btn.isPressed());
        }
    }

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
    uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer,
                                   uint16_t reqlen) {
        // TODO not Implemented
        (void) instance;
        (void) report_id;
        (void) report_type;
        (void) buffer;
        (void) reqlen;

        return 0;
    }

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
    void
    tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer,
                          uint16_t bufsize) {
        (void) instance;

        if (report_type == HID_REPORT_TYPE_OUTPUT) {
            // Set keyboard LED e.g Capslock, Numlock etc...
            if (report_id == REPORT_ID_KEYBOARD) {
                // bufsize should be (at least) 1
                if (bufsize < 1) return;

                uint8_t const kbd_leds = buffer[0];

                if (kbd_leds & KEYBOARD_LED_CAPSLOCK) {
                    // Capslock On: disable blink, turn led on
                    led.setState(true);
                } else {
                    // Caplocks Off: back to normal blink
                    led.setState(false);
                }
            }
        }
    }

    }

    App::App() : statusLed(AppConfig::PIN_LED_STATUS) {
    }

    [[noreturn]] int App::run() {

        puts((
                     brunothg_pico_hid::AppConfig::APP_NAME + "(" + AppConfig::getBoardId() + ")"
                     + ": Version:" + brunothg_pico_hid::AppConfig::APP_VERSION
             ).c_str());

        statusLed.on();
        absolute_time_t timestamp = get_absolute_time();
        while (true) {
            tud_task();
            hid_task();

            if (get_absolute_time() >=
                delayed_by_ms(timestamp, (tud_status_flag == 0) ? 250 : ((tud_status_flag == 1) ? 1000 : 2500))) {
                timestamp = get_absolute_time();
                statusLed.toggle();
            }
        } // END-LOOP

    }


}

