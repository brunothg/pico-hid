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

You can or have to configure some app properties (see CMakeLists.txt):

- GPIO-Pin numbers for buttons and LEDs (required)
- USB VID/PID (vendor/product id) (required for real world use; optional for testing)

# Build

If everything is set up correctly, it should be as easy as running the `build.sh` script.

# Circuit

The required circuit is as simple as the following:

![Pico-HID circuit](https://raw.githubusercontent.com/brunothg/pico-hid/develop/circuit/Circuit.svg)
> [this image was created with Fritzing](https://fritzing.org/)

[//]: # (TODO change urls to master)