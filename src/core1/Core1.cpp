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

#include "hardware/Button.h"
#include "hardware/Led.h"
#include "util/AppConfig.h"
#include "core1/KeyboardTask.h"
#include "core1/MouseTask.h"

namespace brunothg_pico_hid {

    [[noreturn]] void Core1::run() {
        Button btnKeyboard(AppConfig::PIN_BTN_KEYBOARD);
        Led ledKeyboard(AppConfig::PIN_LED_KEYBOARD);
        Button btnMouse(AppConfig::PIN_BTN_MOUSE);
        Led ledMouse(AppConfig::PIN_LED_MOUSE);
        Button btnMouseBtn(AppConfig::PIN_BTN_MOUSE_BUTTON);
        Led ledMouseBtn(AppConfig::PIN_LED_MOUSE_BUTTON);
        Button btnSpeedUp(AppConfig::PIN_BTN_SPEED_UP);
        Button btnSpeedDown(AppConfig::PIN_BTN_SPEED_DOWN);

        KeyboardTask keyboard;
        MouseTask mouse;

        int speed = 0;
        const int maxSpeed = (int) (AppConfig::HID_SPEED_LEVEL_COUNT / 2);
        absolute_time_t speedTimestamp = get_absolute_time();

        while (true) {
            const absolute_time_t timestamp = get_absolute_time();

            // Check speed change
            if (btnSpeedUp.isClicked() && speed < maxSpeed) {
                speed++;
                keyboard.changeSpeedLevel(+1);
                mouse.changeSpeedLevel(+1);
            }
            if (btnSpeedDown.isClicked() && speed > -maxSpeed) {
                speed--;
                keyboard.changeSpeedLevel(-1);
                mouse.changeSpeedLevel(-1);
            }

            // Check keyboard task
            if (btnKeyboard.isClicked()) {
                srand(timestamp);
                keyboard.toggleKeysEnabled();
            }

            // Check mouse task
            if (btnMouse.isClicked()) {
                srand(timestamp);
                mouse.toggleMovementEnabled();
            }

            // Check mouse button task
            if (btnMouseBtn.isClicked()) {
                srand(timestamp);
                mouse.toggleButtonsEnabled();
            }

            if (timestamp >= speedTimestamp) {
                speedTimestamp = delayed_by_ms(timestamp, ((maxSpeed * 100) + 500) - (100 * speed));

                ledKeyboard.setState(keyboard.isKeysEnabled() && !ledKeyboard.getState());
                ledMouse.setState(mouse.isMovementEnabled() && !ledMouse.getState());
                ledMouseBtn.setState(mouse.isButtonsEnabled() && !ledMouseBtn.getState());
            }

            keyboard.run();
            mouse.run();

        }

    }
}
