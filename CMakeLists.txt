# pico-hid - Raspberry Pi Pico HID-Device
# Copyright (C) 2022  Marvin Bruns
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH ".../pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-hid VERSION 1.0.0 LANGUAGES C CXX ASM )

# Enable C++ Exceptions (1=on, 0=off)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
# Enable C++ Real-Time Type-Information (1=on, 0=off)
set(PICO_CXX_ENABLE_RTTI 0)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name
add_executable(pico-hid "")
target_include_directories(pico-hid PRIVATE src)
target_include_directories(pico-hid PUBLIC src/tusb)

pico_set_program_name(pico-hid "${CMAKE_PROJECT_NAME}")
pico_set_program_version(pico-hid "${pico-hid_VERSION_MAJOR}.${pico-hid_VERSION_MINOR}.${pico-hid_VERSION_PATCH}")

# Set console output to UART, USB or none
pico_enable_stdio_uart(pico-hid 1)
pico_enable_stdio_usb(pico-hid 0)

# Add libraries to the build
target_link_libraries(pico-hid PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board)

pico_add_extra_outputs(pico-hid)

# Print flag infos
message("C_FLAGS: ${CMAKE_C_FLAGS}")
message("CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# App config
set(APP_NAME "${CMAKE_PROJECT_NAME}")
set(APP_VERSION "${pico-hid_VERSION_MAJOR}.${pico-hid_VERSION_MINOR}.${pico-hid_VERSION_PATCH}")

# GPIO config
set(APP_GPIO_PIN_LED_STATUS 18)
set(APP_GPIO_PIN_LED_KEYBOARD 15)
set(APP_GPIO_PIN_LED_MOUSE 10)
set(APP_GPIO_PIN_LED_MOUSE_BUTTON 8)
set(APP_GPIO_PIN_BTN_KEYBOARD 14)
set(APP_GPIO_PIN_BTN_MOUSE 12)
set(APP_GPIO_PIN_BTN_MOUSE_BUTTON 11)
set(APP_GPIO_PIN_BTN_SPEED_UP 7)
set(APP_GPIO_PIN_BTN_SPEED_DOWN 3)

# USB config
set(APP_USB_VID 0x1209) # TODO replace test USB VID (0=auto test only)
set(APP_USB_PID 0x0001) # TODO replace test USB PID (0=auto)
set(APP_USB_MANUFACTURER_NAME "NOT YOUR BUSINESS")
set(APP_USB_PRODUCT_NAME "PICO HID")

# add directories
add_subdirectory(src)