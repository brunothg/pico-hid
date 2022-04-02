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
#include "util/AppConfig.h"
#include "HID.h"

namespace brunothg_pico_hid {

    App::App() : statusLed(AppConfig::PIN_LED_STATUS) {
    }

    [[noreturn]] int App::run() {

        puts((
                     brunothg_pico_hid::AppConfig::APP_NAME + "(" + AppConfig::getBoardId() + ")"
                     + ": Version:" + brunothg_pico_hid::AppConfig::APP_VERSION
             ).c_str());

        auto &hid = HID::getInstance();
        Button btn(AppConfig::PIN_BTN_KEYBOARD);

        statusLed.on();
        absolute_time_t ledTimestamp = get_absolute_time();
        absolute_time_t hidTimestamp = get_absolute_time();
        while (true) {
            hid.task();

            // HID task
            if (get_absolute_time() >= delayed_by_ms(hidTimestamp, 100)) {
                hidTimestamp = get_absolute_time();


                switch (hid.getState()) {
                    case Mount:
                        if (btn.isPressed()) {
                            std::shared_ptr<HIDTask> mouseTask = std::make_shared<HIDMouseTask>(0x00, 5, 5, 0, 0);

                            std::vector<uint8_t> keycode{HID_KEY_A, 0, 0, 0, 0, 0};
                            std::shared_ptr<HIDTask> keyboardATask = std::make_shared<HIDKeyboardTask>(0, keycode);
                            std::shared_ptr<HIDTask> keyboardNullTask = std::make_shared<HIDKeyboardTask>(0);

                            hid.scheduleHidTasks({mouseTask, keyboardATask, keyboardNullTask});
                        }
                        break;
                    case Suspended:
                        hid.remoteWakeup();
                        break;
                    case Unmount:
                    default:
                        break;
                }

            }

            // LED task
            auto usbState = hid.getState();
            if (get_absolute_time() >=
                delayed_by_ms(ledTimestamp, (usbState == Unmount) ? 250 : ((usbState == Mount) ? 1000 : 2500))) {
                ledTimestamp = get_absolute_time();
                statusLed.toggle();
            }
        } // END-LOOP

    }


}

