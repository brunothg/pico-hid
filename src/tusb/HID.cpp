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

#include "HID.h"

#include <tusb.h>
#include <bsp/board.h>
#include "tusb_descriptors.h"

namespace brunothg_pico_hid {

    StateChangeEvent::StateChangeEvent(TUSB_State oldState, TUSB_State newState): oldState{oldState}, newState{newState} {
    }

    HID::HID() : state{Unmount} {
    }

    void HID::setState(TUSB_State newState) {
        auto oldState = state;
        state = newState;

        dispatchEvent(StateChangeEvent(oldState, newState));
    }

    TUSB_State HID::getState() const {
        return state;
    }

    void HID::setRemoteWakeupEnabled(bool newRemoteWakeupEnabled) {
        remoteWakeupEnabled = newRemoteWakeupEnabled;
    }

    bool HID::isRemoteWakeupEnabled() const {
        return remoteWakeupEnabled;
    }

    extern "C" {

    //--------------------------------------------------------------------+
    // Device callbacks
    //--------------------------------------------------------------------+

    // Invoked when device is mounted
    void tud_mount_cb(void) {
        HID &hid = HID::getInstance();
        hid.setState(Mount);
    }

    // Invoked when device is unmounted
    void tud_umount_cb(void) {
        HID &hid = HID::getInstance();
        hid.setState(Unmount);
    }

    // Invoked when usb bus is suspended
    // remote_wakeup_en : if host allow us  to perform remote wakeup
    // Within 7ms, device must draw an average of current less than 2.5 mA from bus
    void tud_suspend_cb(bool remote_wakeup_en) {
        HID &hid = HID::getInstance();
        hid.setRemoteWakeupEnabled(remote_wakeup_en);
        hid.setState(Suspended);
    }

    // Invoked when usb bus is resumed
    void tud_resume_cb(void) {
        HID &hid = HID::getInstance();
        hid.setState(Mount);
    }

    //--------------------------------------------------------------------+
    // USB HID
    //--------------------------------------------------------------------+


    }

}
