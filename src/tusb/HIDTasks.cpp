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

#include "HIDTasks.h"
#include <tusb.h>
#include "tusb_descriptors.h"

namespace brunothg_pico_hid {

    HIDMouseTask::HIDMouseTask(uint8_t buttons, int8_t x, int8_t y, int8_t vertical,
                               int8_t horizontal) : buttons{buttons}, x{x}, y{y}, vertical{vertical},
                                                    horizontal{horizontal} {
    }

    void HIDMouseTask::task() {
        tud_hid_mouse_report(REPORT_ID_MOUSE, buttons, x, y, vertical, horizontal);
    }

    HIDKeyboardTask::HIDKeyboardTask(uint8_t modifier, std::vector<uint8_t> keycode) : modifier{modifier},
                                                                                       keycode{keycode.begin(),
                                                                                               keycode.begin() +
                                                                                               (int) std::min(
                                                                                                       keycode.size(),
                                                                                                       6u)} {
    }

    void HIDKeyboardTask::task() {
        if (keycode.empty()) {
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, nullptr);
        } else {
            uint8_t keycodeArray[6] = {0};
            int index = 0;
            for (auto keyc: keycode) {
                keycodeArray[index] = keyc;
                index++;
            }
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycodeArray);
        }
    }

}
