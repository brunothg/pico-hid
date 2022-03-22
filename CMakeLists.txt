cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH ".../pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-hid C CXX ASM)

# Enable C++ Exceptions (1=on, 0=off)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
# Enable C++ Real-Time Type-Information (1=on, 0=off)
set(PICO_CXX_ENABLE_RTTI 0)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name
add_executable(pico-hid "")
target_include_directories(pico-hid PRIVATE .)

pico_set_program_name(pico-hid "pico-hid")
pico_set_program_version(pico-hid "1.0.0")

# Set console output to UART, USB or none
pico_enable_stdio_uart(pico-hid 1)
pico_enable_stdio_usb(pico-hid 0)

# Add libraries to the build
target_link_libraries(pico-hid pico_stdlib)

pico_add_extra_outputs(pico-hid)

# add directories
add_subdirectory(src)

# Print flag infos
message("C_FLAGS: ${CMAKE_C_FLAGS}")
message("CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
