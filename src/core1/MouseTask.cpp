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

#include "MouseTask.h"

#include "HID.h"

namespace brunothg_pico_hid {

    MouseTask::MouseTask() : buttonsEnabled{false}, movementEnabled{false}, runTimestamp{get_absolute_time()} {

    }

    void MouseTask::setMovementEnabled(bool enabled) {
        movementEnabled = enabled;
    }

    void MouseTask::toggleMovementEnabled() {
        setMovementEnabled(!isMovementEnabled());
    }

    bool MouseTask::isMovementEnabled() const {
        return movementEnabled;
    }

    void MouseTask::setButtonsEnabled(bool enabled) {
        buttonsEnabled = enabled;
    }

    void MouseTask::toggleButtonsEnabled() {
        setButtonsEnabled(!isButtonsEnabled());
    }

    bool MouseTask::isButtonsEnabled() const {
        return buttonsEnabled;
    }

    void MouseTask::run() {
        if (!movementEnabled && !buttonsEnabled) {
            return;
        }
        auto &hid = HID::getInstance();

        if (get_absolute_time() >= delayed_by_ms(runTimestamp, 1000 - (100 * getSpeed()))) {
            runTimestamp = get_absolute_time();

            if (movementEnabled) {
                std::shared_ptr<HIDTask> mouseMoveTask = std::make_shared<HIDMouseTask>(0x00, 5, 5, 0, 0);
                hid.scheduleHidTask(mouseMoveTask);
            }

            if (buttonsEnabled) {
                std::shared_ptr<HIDTask> mouseClickTask = std::make_shared<HIDMouseTask>(MOUSE_BUTTON_RIGHT, 0, 0, 0, 0);
                std::shared_ptr<HIDTask> mouseReleaseTask = std::make_shared<HIDMouseTask>(0x00, 0, 0, 0, 0);
                hid.scheduleHidTasks({mouseClickTask, mouseReleaseTask});
            }
        }
        // TODO run mouse
    }

}
