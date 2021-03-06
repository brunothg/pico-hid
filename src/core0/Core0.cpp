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

#include "Core0.h"

#include <pico/stdlib.h>
#include "HID.h"
#include "hardware/Led.h"
#include "util/AppConfig.h"

namespace brunothg_pico_hid {

    [[noreturn]] void Core0::run() {
        auto &hid = HID::getInstance();
        Led statusLed(AppConfig::PIN_LED_STATUS, true);

        absolute_time_t statusTimestamp = get_absolute_time();
        while (true) {
            // TUSB task
            hid.task();
            hid.remoteWakeup();

            // Status-LED task
            auto usbState = hid.getState();
            if (get_absolute_time() >=
                delayed_by_ms(statusTimestamp, (usbState == Unmount) ? 250 : ((usbState == Mount) ? 1000 : 2500))) {
                statusTimestamp = get_absolute_time();
                statusLed.toggle();
            }
        }
    }

}
