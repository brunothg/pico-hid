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

#ifndef PICO_HID_APP_H
#define PICO_HID_APP_H

#include "pico/stdlib.h"
#include "hardware/Led.h"

namespace brunothg_pico_hid {

    class App {
    private:
        LED statusLed;

    public:
        App();

        /**
         * Start method
         * @return Return code
         */
        [[noreturn]] int run();
    };

}

#endif //PICO_HID_APP_H
