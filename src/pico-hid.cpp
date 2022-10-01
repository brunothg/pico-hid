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

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <bsp/board.h>
#include <tusb.h>

#include "util/AppConfig.h"
#include "core0/Core0.h"
#include "core1/Core1.h"

void core0_func() {
    brunothg_pico_hid::Core0::run();
}

void core1_func() {
    brunothg_pico_hid::Core1::run();
}

int main() {
    stdio_init_all();
    board_init();
    tusb_init();

    puts((
                 brunothg_pico_hid::AppConfig::APP_NAME + "(" + brunothg_pico_hid::AppConfig::getBoardId() + ")"
                 + ": Version:" + brunothg_pico_hid::AppConfig::APP_VERSION
         ).c_str());

    multicore_launch_core1(core1_func);
    core0_func();
}
