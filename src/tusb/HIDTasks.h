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

#ifndef PICO_HID_HIDTASKS_H
#define PICO_HID_HIDTASKS_H

#include <pico/stdlib.h>
#include <vector>

namespace brunothg_pico_hid {

    class HID;

    class HIDTask {
        friend class HID;

    private:
        /**
         * Run the HID task
         */
        virtual void task() = 0;

    public:
        virtual ~HIDTask() = default;
    };

    /**
     * Represents a HID mouse task
     * @see tud_hid_mouse_report
     */
    struct HIDMouseTask : HIDTask {
        /**
         * Mouse buttons
         */
        const uint8_t buttons;

        /**
         * X-axis mouse movement
         */
        const int8_t x;

        /**
         * Y-axis mouse movement
         */
        const int8_t y;

        /**
         * Vertical mouse wheel movement
         */
        const int8_t vertical;

        /**
         * Horizontal mouse wheel movement
         */
        const int8_t horizontal;

        HIDMouseTask(uint8_t buttons, int8_t x, int8_t y, int8_t vertical, int8_t horizontal);

        void task() override;
    };

    /**
    * Represents a HID keyboard task
    * @see tud_hid_keyboard_report
    */
    struct HIDKeyboardTask : HIDTask {

        /**
         * Key modifiers
         */
        const uint8_t modifier;

        /**
         * Keycode array with up to six elements (0 elements -> release)
         */
        const std::vector<uint8_t> keycode;

        HIDKeyboardTask(uint8_t modifier, std::vector<uint8_t> keycode = std::vector<uint8_t>());

        void task() override;
    };

}

#endif //PICO_HID_HIDTASKS_H
