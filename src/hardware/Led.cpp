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

#include "Led.h"

namespace brunothg_pico_hid {

    LED::LED(uint pin, bool state) : pin{pin}, state{state} {
        init();
    }

    void LED::init() const {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }

    void LED::setState(bool newState) {
        state = newState;
        gpio_put(pin, state);
    }

    bool LED::getState() {
        return state;
    }

    void LED::on() {
        setState(true);
    }

    void LED::off() {
        setState(false);
    }
}