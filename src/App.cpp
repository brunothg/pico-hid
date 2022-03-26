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
#include "hardware/Button.h"

namespace brunothg_pico_hid {

    App::App() : statusLed(AppConfig::PIN_LED_STATUS) {
    }

    [[noreturn]] int App::run() {
        stdio_init_all();

        puts((
                     brunothg_pico_hid::AppConfig::APP_NAME + ": Version:" + brunothg_pico_hid::AppConfig::APP_VERSION
             ).c_str());

        Button btnKeyboard(AppConfig::PIN_BTN_KEYBOARD);
        Led ledKeyboard(AppConfig::PIN_LED_KEYBOARD);

        Button btnMouse(AppConfig::PIN_BTN_MOUSE);
        Led ledMouse(AppConfig::PIN_LED_MOUSE);

        Button btnMouseBtn(AppConfig::PIN_BTN_MOUSE_BUTTON);
        Led ledMouseBtn(AppConfig::PIN_LED_MOUSE_BUTTON);

        Button btnUp(AppConfig::PIN_BTN_SPEED_UP);
        Button btnDown(AppConfig::PIN_BTN_SPEED_DOWN);

        statusLed.on();
        uint32_t waitTime = 1750;
        while(true) {
            sleep_ms(waitTime);
            statusLed.toggle();

            ledKeyboard.setState(btnKeyboard.isPressed());
            ledMouse.setState(btnMouse.isPressed());
            ledMouseBtn.setState(btnMouseBtn.isPressed());

            if(btnUp.isPressed()) {
                waitTime = std::max(500uL, waitTime - 100);
            }
            else if (btnDown.isPressed()) {
                waitTime = std::min(waitTime - 100, 2000uL);
            }
        }

    }



}
