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

I decided to add a little (functional - not beautiful) case. So i had to provide a extra green LED as a replacement for
the on board LED, as it is no longer reachable or visible. For the same reason there are two extra buttons on the bottom
side for Reset (RUN-Pin to ground) and BOOTSEL (TP6 to ground). For debugging purposes there are also UART-pins soldered
on the Pico.

![Circuit in housing](https://github.com/brunothg/pico-hid/raw/develop/circuit/circuit_soldered_housing.jpg)
> circuit in his case

![Circuit front side](https://github.com/brunothg/pico-hid/raw/develop/circuit/circuit_soldered_front.jpg)
> circuit front side

![Circuit back side](https://github.com/brunothg/pico-hid/raw/develop/circuit/circuit_soldered_back.jpg)
> circuit back side (GND solder point on the top-left is wrong -> should be GP18)

[//]: # (TODO change urls to master)