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

#include "util/AppConfig.h"

namespace brunothg_pico_hid {

    const std::string AppConfig::APP_NAME = "${app_NAME}";
    const std::string AppConfig::APP_VERSION = "${app_VERSION}";

    /**
     * GPIO definitions
     */
    const uint AppConfig::PIN_LED_STATUS = 18;
    const uint AppConfig::PIN_LED_KEYBOARD = 15;
    const uint AppConfig::PIN_LED_MOUSE = 10;
    const uint AppConfig::PIN_LED_MOUSE_BUTTON = 8;
    const uint AppConfig::PIN_BTN_KEYBOARD = 14;
    const uint AppConfig::PIN_BTN_MOUSE = 12;
    const uint AppConfig::PIN_BTN_MOUSE_BUTTON = 11;
    const uint AppConfig::PIN_BTN_SPEED_UP = 7;
    const uint AppConfig::PIN_BTN_SPEED_DOWN = 3;
}
