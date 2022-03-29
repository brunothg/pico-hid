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

#ifndef PICO_HID_HID_H
#define PICO_HID_HID_H

#include "util/EventDispatcher.h"

namespace brunothg_pico_hid {

    extern "C" {
    void tud_mount_cb(void);
    void tud_umount_cb(void);
    void tud_suspend_cb(bool remote_wakeup_en);
    void tud_resume_cb(void);
    }

    /**
     * TinyUsb connection states
     */
    enum TUSB_State {
        Unmount,
        Mount,
        Suspended
    };

    struct StateChangeEvent : Event {
        const TUSB_State oldState;
        const TUSB_State newState;

        StateChangeEvent(TUSB_State oldState, TUSB_State newState);
    };

    class HID : EventDispatcher {
        friend void tud_mount_cb();

        friend void tud_umount_cb();

        friend void tud_suspend_cb(bool);

        friend void tud_resume_cb();

    public:
        /**
         * Singleton instance
         * @return HID singleton instance
         */
        static HID &getInstance() {
            static HID instance;
            return instance;
        }

    private:
        /**
         * Actual state
         */
        TUSB_State state;

        /**
         * true, if remote wakeup is enabled (only valid in suspend state)
         */
        bool remoteWakeupEnabled;

        HID();

        void setState(TUSB_State newState);

        void setRemoteWakeupEnabled(bool newRemoteWakeupEnabled);

    public:
        HID(HID const &) = delete;

        void operator=(HID const &) = delete;

        TUSB_State getState() const;

        bool isRemoteWakeupEnabled() const;
    };

}

#endif //PICO_HID_HID_H
