# pico-hid
Raspberry Pi Pico HID-Device

# Dependencies
The following dependencies must be installed (see dependencies.sh):
- [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) incl. `PICO_SDK_PATH` environment variable
- [TinyUSB](https://github.com/hathach/tinyusb) (for HID support - should be part of Pico's SDK)
- C/C++ build environment and tools (gcc, make, ...)
- [Doxygen](https://www.doxygen.nl/index.html) (for docs)
- [TexLive](https://www.tug.org/texlive/) (for docs)

# Configuration
You can or have to configure some app properties:
- GPIO-Pin numbers for buttons and LEDs (see CMakeLists.txt)
