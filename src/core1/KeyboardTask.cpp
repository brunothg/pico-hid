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

#include "KeyboardTask.h"
#include <cmath>

#include "HID.h"
#include "util/AppConfig.h"

namespace brunothg_pico_hid {

    KeyboardTask::KeyboardTask() : keysEnabled(false), runTimestamp{get_absolute_time()} {
    }

    void KeyboardTask::setKeysEnabled(bool enabled) {
        keysEnabled = enabled;
    }

    void KeyboardTask::toggleKeysEnabled() {
        setKeysEnabled(!isKeysEnabled());
    }

    bool KeyboardTask::isKeysEnabled() const {
        return keysEnabled;
    }

    uint8_t calculateRandomKeyCode() {
        auto keycode = HID_KEY_A + (uint8_t) std::floor((HID_KEY_SPACE - HID_KEY_A) * ((double) rand() / RAND_MAX));
        switch (keycode) {
            case HID_KEY_ESCAPE:
                keycode = HID_KEY_SPACE;
                break;
        }

        return keycode;
    }

    void KeyboardTask::run() {
        if (!keysEnabled) {
            return;
        }
        auto &hid = HID::getInstance();
        const absolute_time_t timestamp = get_absolute_time();

        if (timestamp >= runTimestamp) {
            runTimestamp = delayed_by_ms(timestamp,calculateRandomisedDelay());

            std::vector<uint8_t> keycode{calculateRandomKeyCode()};
            std::shared_ptr<HIDTask> keyboardATask = std::make_shared<HIDKeyboardTask>(0, keycode);
            std::shared_ptr<HIDTask> keyboardNullTask = std::make_shared<HIDKeyboardTask>(0);

            hid.scheduleHidTasks({keyboardATask, keyboardNullTask});
        }

    }


}
