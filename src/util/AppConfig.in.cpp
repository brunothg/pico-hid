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

#include <cstring>
#include <pico/unique_id.h>

namespace brunothg_pico_hid {

    const std::string AppConfig::APP_NAME = "${APP_NAME}";
    const std::string AppConfig::APP_VERSION = "${APP_VERSION}";

    /*
     * GPIO definitions
     */
    const uint AppConfig::PIN_LED_STATUS = ${APP_GPIO_PIN_LED_STATUS};
    const uint AppConfig::PIN_LED_KEYBOARD = ${APP_GPIO_PIN_LED_KEYBOARD};
    const uint AppConfig::PIN_LED_MOUSE = ${APP_GPIO_PIN_LED_MOUSE};
    const uint AppConfig::PIN_LED_MOUSE_BUTTON = ${APP_GPIO_PIN_LED_MOUSE_BUTTON};
    const uint AppConfig::PIN_BTN_KEYBOARD = ${APP_GPIO_PIN_BTN_KEYBOARD};
    const uint AppConfig::PIN_BTN_MOUSE = ${APP_GPIO_PIN_BTN_MOUSE};
    const uint AppConfig::PIN_BTN_MOUSE_BUTTON = ${APP_GPIO_PIN_BTN_MOUSE_BUTTON};
    const uint AppConfig::PIN_BTN_SPEED_UP = ${APP_GPIO_PIN_BTN_SPEED_UP};
    const uint AppConfig::PIN_BTN_SPEED_DOWN = ${APP_GPIO_PIN_BTN_SPEED_DOWN};

    /*
     * USB configurations
     */
    const uint16_t AppConfig::USB_VID = ${APP_USB_VID};
    const uint16_t AppConfig::USB_PID = ${APP_USB_PID};
    const std::string AppConfig::USB_MANUFACTURER_NAME = "${APP_USB_MANUFACTURER_NAME}";
    const std::string AppConfig::USB_PRODUCT_NAME = "${APP_USB_PRODUCT_NAME}";

    std::string AppConfig::boardId;

    std::string AppConfig::getBoardId() {
        if (boardId.empty()) {
            pico_unique_board_id_t picoUniqueBoardId;
            pico_get_unique_board_id(&picoUniqueBoardId);
            uint64_t boardIdNumber = 0;
            std::memcpy(&boardIdNumber, picoUniqueBoardId.id, 8);
            boardId = std::to_string(boardIdNumber);
        }

        return boardId;
    }

}
