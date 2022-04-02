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

#ifndef PICO_HID_MOUSETASK_H
#define PICO_HID_MOUSETASK_H

#include <pico/stdlib.h>
#include "AbstractTask.h"

namespace brunothg_pico_hid {

    class MouseTask : public AbstractTask {
    private:
        bool movementEnabled;
        bool buttonsEnabled;
        absolute_time_t runTimestamp;

    public:
        MouseTask();

        void setMovementEnabled(bool enabled);

        void toggleMovementEnabled();

        [[nodiscard]] bool isMovementEnabled() const;

        void setButtonsEnabled(bool enabled);

        void toggleButtonsEnabled();

        [[nodiscard]] bool isButtonsEnabled() const;

        void run() override;
    };

}

#endif //PICO_HID_MOUSETASK_H
