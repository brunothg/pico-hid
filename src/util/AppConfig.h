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

#ifndef PICO_HID_APPCONFIG_H
#define PICO_HID_APPCONFIG_H

#include <string>
#include "pico/stdlib.h"

namespace brunothg_pico_hid {

    /**
     * App configuration information.
     *
     * @author Marvin Bruns
     */
    class AppConfig {
    private:
        static std::string boardId;

    public:
        /**
         * The name of this app
         */
        static const std::string APP_NAME;

        /**
         * The version of this app
         */
        static const std::string APP_VERSION;

        /**
         * The main status LED pin nr
         */
        static const uint PIN_LED_STATUS;

        /**
         * The keyboard status LED pin nr
         */
        static const uint PIN_LED_KEYBOARD;

        /**
         * The mouse status LED pin nr
         */
        static const uint PIN_LED_MOUSE;

        /**
         * The mouse buttons status LED pin nr
         */
        static const uint PIN_LED_MOUSE_BUTTON;

        /**
         * The keyboard button pin nr
         */
        static const uint PIN_BTN_KEYBOARD;

        /**
         * The mouse button pin nr
         */
        static const uint PIN_BTN_MOUSE;

        /**
         * The mouse buttons button pin nr
         */
        static const uint PIN_BTN_MOUSE_BUTTON;

        /**
         * The speed-up button pin nr
         */
        static const uint PIN_BTN_SPEED_UP;

        /**
         * The speed-down button pin nr
         */
        static const uint PIN_BTN_SPEED_DOWN;

        /**
         * USB vendor id (0 for auto mode - test only)
         */
        static const uint16_t USB_VID;

        /**
        * USB product id (0 for auto mode)
        */
        static const uint16_t USB_PID;

        /**
         * USB manufacturer name
         */
        static const std::string USB_MANUFACTURER_NAME;

        /**
         * USB product name
         */
        static const std::string USB_PRODUCT_NAME;

        /**
         * Get the board id as string
         * @see pico_get_unique_board_id_string
         * @return The board id
         */
        static std::string getBoardId();

    };

}

#endif //PICO_HID_APPCONFIG_H
