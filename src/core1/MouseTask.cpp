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

#include <cmath>
#include "HID.h"
#include "util/AppConfig.h"

namespace brunothg_pico_hid {

    MouseTask::MouseTask() : buttonsEnabled{false}, movementEnabled{false}, runTimestampMovement{get_absolute_time()},
                             runTimestampClick{get_absolute_time()} {

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
        const absolute_time_t timestamp = get_absolute_time();

        if (movementEnabled && timestamp > runTimestampMovement) {
            runTimestampMovement = delayed_by_ms(timestamp, calculateRandomisedDelay());

            if (targetX == posX && targetY == posY) {
                calculateNewTarget();
            }

            int dx = (targetX == posX) ? 0 : ((targetX > posX) ? 1 : -1);
            int dy = (targetY == posY) ? 0 : ((targetY > posY) ? 1 : -1);

            std::shared_ptr<HIDTask> mouseMoveTask = std::make_shared<HIDMouseTask>(0x00, dx, dy, 0, 0);
            auto success = hid.scheduleHidTask(mouseMoveTask);
            if (success) {
                posX += dx;
                posY += dy;
            }
        }

        if (buttonsEnabled && timestamp > runTimestampClick) {
            runTimestampClick = delayed_by_ms(timestamp, calculateRandomisedDelay());

            // TODO run mouse click
            std::shared_ptr<HIDTask> mouseClickTask = std::make_shared<HIDMouseTask>(MOUSE_BUTTON_RIGHT, 0, 0, 0,
                                                                                     0);
            std::shared_ptr<HIDTask> mouseReleaseTask = std::make_shared<HIDMouseTask>(0x00, 0, 0, 0, 0);
            hid.scheduleHidTasks({mouseClickTask, mouseReleaseTask});
        }

    }

    void MouseTask::calculateNewTarget() {
        targetX = (uint32_t) std::floor(800.0 * ((double) rand() / RAND_MAX));
        targetY = (uint32_t) std::floor(600.0 * ((double) rand() / RAND_MAX));
    }

}
