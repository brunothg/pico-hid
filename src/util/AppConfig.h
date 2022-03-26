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

#ifndef PICO_HID_APPCONFIG_H
#define PICO_HID_APPCONFIG_H

#include <string>

namespace brunothg_pico_hid {

    /**
     * App configuration information.
     *
     * @author Marvin Bruns
     */
    class AppConfig {
    public:
        /**
         * The name of this app
         */
        static const std::string appName;

        /**
         * The version of this app
         */
        static const std::string appVersion;

    };

}

#endif //PICO_HID_APPCONFIG_H
