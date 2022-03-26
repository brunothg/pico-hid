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

#ifndef PICO_HID_LED_H
#define PICO_HID_LED_H

#include "pico/stdlib.h"

namespace brunothg_pico_hid {

    class LED {
    private:
        /**
         * LED GPIO pin nr
         */
        uint pin;

        /**
         * ON=true, OFF=false
         */
        bool state;

        /**
         * Initialize hardware
         */
        void init() const;

    public:
        explicit LED(uint pin, bool state = false);

        /**
         * Set the LED state (ON=true, OFF=false)
         * @param newState The new LED state
         */
        void setState(bool newState);

        /**
         * Get the LED state
         * @return true if the LED state is ON otherwise false
         */
        bool getState();

        /**
         * Turn LED on
         */
        void on();

        /**
         * Turn LED off
         */
        void off();
    };

}

#endif //PICO_HID_LED_H
