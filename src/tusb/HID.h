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

#include <tusb.h>
#include <bsp/board.h>
#include <pico/critical_section.h>
#include <queue>
#include <memory>
#include "tusb_descriptors.h"
#include "TUsbConnectionState.h"
#include "util/EventDispatcher.h"
#include "HIDTasks.h"

namespace brunothg_pico_hid {

    extern "C" {
    /**
     * Invoked when device is mounted
     * @see tud_mount_cb
     */
    void tud_mount_cb_HID();

    /**
     * Invoked when device is unmounted
     * @see tud_umount_cb
     */
    void tud_umount_cb_HID();

    /**
     * Invoked when usb bus is suspended
     * remote_wakeup_en : if host allow us  to perform remote wakeup
     * Within 7ms, device must draw an average of current less than 2.5 mA from bus
     * @see tud_suspend_cb
     */
    void tud_suspend_cb_HID(bool);

    /**
     * Invoked when usb bus is resumed
     * @see tud_resume_cb
     */
    void tud_resume_cb_HID();

    /**
     * Invoked when received GET_REPORT control request
     * Application must fill buffer report's content and return its length.
     * Return zero will cause the stack to STALL request
     * @return Buffer length or 0 to STALL request
     * @see tud_hid_get_report_cb
     */
    uint16_t tud_hid_get_report_cb_HID(uint8_t, uint8_t, hid_report_type_t, uint8_t *, uint16_t);

    /**
     * Invoked when sent REPORT successfully to host
     * Application can use this to send the next report
     * Note: For composite reports, report[0] is report ID
     *
     * @see tud_hid_report_complete_cb
     */
    void tud_hid_report_complete_cb_HID(uint8_t, uint8_t const *, uint8_t);

    /**
     * Invoked when received SET_REPORT control request or
     * received data on OUT endpoint ( Report ID = 0, Type = 0 )
     *
     * @see tud_hid_set_report_cb
     */
    void tud_hid_set_report_cb_HID(uint8_t, uint8_t, hid_report_type_t, uint8_t const *, uint16_t);
    };

    class HID : EventDispatcher {
        friend void tud_mount_cb_HID();

        friend void tud_umount_cb_HID();

        friend void tud_suspend_cb_HID(bool);

        friend void tud_resume_cb_HID();

        friend uint16_t tud_hid_get_report_cb_HID(uint8_t, uint8_t, hid_report_type_t, uint8_t *, uint16_t);

        friend void tud_hid_report_complete_cb_HID(uint8_t, uint8_t const *, uint8_t);

        friend void tud_hid_set_report_cb_HID(uint8_t, uint8_t, hid_report_type_t, uint8_t const *, uint16_t);

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
        TUsbConnectionState state;

        /**
         * true, if remote wakeup is enabled (only valid in suspend state)
         */
        bool remoteWakeupEnabled;

        /**
         * Queued HID tasks
         */
        std::queue<std::shared_ptr<HIDTask>> hidTasks;

        /**
         * Sync section for HID tasks
         * @see hidTasks
         */
        critical_section_t hidTaskSection;

        /**
         * True, if there is an HID task running
         */
        bool hidTaskRunning;

        HID();

        ~HID() override;

        void setState(TUsbConnectionState newState);

        void setRemoteWakeupEnabled(bool newRemoteWakeupEnabled);

        void onReportCompleted(uint8_t instance, uint8_t const *report, uint8_t len);

        void onSetReport(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer,
                         uint16_t bufsize);

        /**
         * Try to run next HID task, if no one is running (thread safe)
         * @see hidTaskRunning
         */
        void runNextHidTask();

    public:
        HID(HID const &) = delete;

        void operator=(HID const &) = delete;

        [[nodiscard]] TUsbConnectionState getState() const;

        [[nodiscard]] bool isRemoteWakeupEnabled() const;

        /**
         * Test, if there are any running HID tasks
         * @return true, if any task is running, otherwise false
         */
        [[nodiscard]] bool isHidTaskRunning() const;

        /**
         * Wakeup host if possible
         */
        void remoteWakeup() const;

        /**
         * Schedule HID task (thread safe)
         * @param va_hidTasks HID tasks that should be scheduled
         */
        void scheduleHidTasks(std::initializer_list<std::shared_ptr<HIDTask>> va_hidTasks);

        /**
         * @see scheduleHidTask(std::initializer_list<std::shared_ptr<HIDTask>> va_hidTasks)
         */
        inline void scheduleHidTask(std::shared_ptr<HIDTask> &hidTask) {
            scheduleHidTasks({hidTask});
        }

        /**
         * Run HID task
         * @see void tud_task(void)
         */
        void task();
    };

}

#endif //PICO_HID_HID_H
