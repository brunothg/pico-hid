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

#include "Button.h"

namespace brunothg_pico_hid {

    Button::Button(uint pin, int pullResistor) : pin{pin},
                                                 pullResistor{pullResistor},
                                                 state{false},
                                                 debounceTime{get_absolute_time()} {
        init();
    }

    void Button::init() {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        if (pullResistor == 1) gpio_pull_down(pin);
        if (pullResistor == 2) gpio_pull_up(pin);

        debounceTime = get_absolute_time();
    }

    bool Button::isPressed() {
        absolute_time_t timestamp = get_absolute_time();
        bool newState = (std::abs(pullResistor) == 1) == gpio_get(pin);
        bool debouncePassed = timestamp > delayed_by_ms(debounceTime, 50);
        if (debouncePassed) {
            debounceTime = timestamp;
            state = newState;
        }

        return state;
    }

    bool Button::isClicked() {
        bool previousState = state;
        bool newState = isPressed();

        return previousState && !newState;
    }

}
