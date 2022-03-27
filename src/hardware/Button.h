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

#ifndef PICO_HID_BUTTON_H
#define PICO_HID_BUTTON_H

#include <pico/stdlib.h>
#include <map>

namespace brunothg_pico_hid {

    class Button {
    private:
        /**
         * Button GPIO pin nr
         */
        const uint pin;

        /**
         * Pull-down or pull-up resistor state.
         * 1=internal-pull-down, 2=internal-pull-up
         * , -1=external-pull-down, 2=external-pull-up.
         */
         const int pullResistor;

        /**
         * Pressed=true, Released=false
         */
        bool state;

        /**
         * Timestamp used for debouncing
         */
        absolute_time_t debounceTime;

        /**
         * Initialize hardware
         */
        void init();

    public:
        explicit Button(uint pin, int pullResistor = 2);

        /**
         * Test, if the button ist pressed
         * @return true, if the button is pressed, otherwise false
         */
        [[nodiscard]] bool isPressed();
    };

}

#endif //PICO_HID_BUTTON_H
