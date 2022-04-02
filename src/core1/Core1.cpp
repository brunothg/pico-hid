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

#include "Core1.h"

#include <pico/stdlib.h>
#include "HID.h"
#include "hardware/Button.h"
#include "hardware/Led.h"
#include "util/AppConfig.h"

namespace brunothg_pico_hid {

    [[noreturn]] void Core1::run() {
        auto &hid = HID::getInstance();
        Button btn(AppConfig::PIN_BTN_KEYBOARD);
        Led led(AppConfig::PIN_LED_KEYBOARD);

        absolute_time_t hidTimestamp = get_absolute_time();
        while(true) {

            if (get_absolute_time() >= delayed_by_ms(hidTimestamp, 100)) {
                hidTimestamp = get_absolute_time();

                led.setState(btn.isPressed());
                if (btn.isPressed()) {
                    std::shared_ptr<HIDTask> mouseTask = std::make_shared<HIDMouseTask>(0x00, 5, 5, 0, 0);

                    std::vector<uint8_t> keycode{HID_KEY_A, 0, 0, 0, 0, 0};
                    std::shared_ptr<HIDTask> keyboardATask = std::make_shared<HIDKeyboardTask>(0, keycode);
                    std::shared_ptr<HIDTask> keyboardNullTask = std::make_shared<HIDKeyboardTask>(0);

                    hid.scheduleHidTasks({mouseTask, keyboardATask, keyboardNullTask});
                }
            }

        }
        // TODO core 1
    }
}
