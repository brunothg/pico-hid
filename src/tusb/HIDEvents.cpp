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

#include "HIDEvents.h"

namespace brunothg_pico_hid {

    TUsbStateChangeEvent::TUsbStateChangeEvent(TUsbConnectionState oldState, TUsbConnectionState newState) : oldState{
            oldState},
                                                                                                             newState{
                                                                                                                     newState} {
    }

    TUsbReportCompleteEvent::TUsbReportCompleteEvent(uint8_t instance, const uint8_t *report, uint8_t len) : instance{
            instance}, report{report}, len{len} {
    }

    TUsbSetReportEvent::TUsbSetReportEvent(uint8_t instance, uint8_t report_id, hid_report_type_t report_type,
                                           const uint8_t *buffer, uint16_t bufsize) : instance{instance},
                                                                                      report_id{report_id},
                                                                                      report_type{report_type},
                                                                                      buffer{buffer}, bufsize{bufsize} {
    }

}
