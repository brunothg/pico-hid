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

#ifndef PICO_HID_HIDEVENTS_H
#define PICO_HID_HIDEVENTS_H

#include <pico/stdlib.h>
#include <tusb.h>
#include "util/Event.h"
#include "TUsbConnectionState.h"

namespace brunothg_pico_hid {

    /**
     * This event occurs, when the USB-connection-state changed
     */
    struct TUsbStateChangeEvent : Event {
        const TUsbConnectionState oldState;
        const TUsbConnectionState newState;

        TUsbStateChangeEvent(TUsbConnectionState oldState, TUsbConnectionState newState);
    };

    struct TUsbReportCompleteEvent : Event {
        /**
         * The instance id
         */
        const uint8_t instance;

        /**
         * Received report.
         * Note: For composite reports, report[0] is report ID
         */
        const uint8_t *report;

        /**
         * Report length
         */
        const uint8_t len;

        TUsbReportCompleteEvent(uint8_t instance, const uint8_t *report, uint8_t len);
    };

    struct TUsbSetReportEvent : Event {
        const uint8_t instance;
        const uint8_t report_id;
        const hid_report_type_t report_type;
        const uint8_t *buffer;
        const uint16_t bufsize;

        TUsbSetReportEvent(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, const uint8_t *buffer,
                           uint16_t bufsize);
    };

}

#endif //PICO_HID_HIDEVENTS_H
