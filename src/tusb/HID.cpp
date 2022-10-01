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

#include "HIDEvents.h"

namespace brunothg_pico_hid {

    HID::HID() : state{Unmount}, hidTaskRunning{false}, remoteWakeupEnabled{false}, hidTaskSection() {
        critical_section_init(&hidTaskSection);
    }

    HID::~HID() {
        critical_section_deinit(&hidTaskSection);
    }

    void HID::setState(TUsbConnectionState newState) {
        auto oldState = state;
        state = newState;

        dispatchEvent(TUsbStateChangeEvent(oldState, newState));
    }

    TUsbConnectionState HID::getState() const {
        return state;
    }

    void HID::setRemoteWakeupEnabled(bool newRemoteWakeupEnabled) {
        remoteWakeupEnabled = newRemoteWakeupEnabled;
    }

    bool HID::isRemoteWakeupEnabled() const {
        return remoteWakeupEnabled;
    }

    void HID::onReportCompleted(uint8_t instance, const uint8_t *report, uint8_t len) {
        hidTaskRunning = false;
        dispatchEvent(TUsbReportCompleteEvent(instance, report, len));
    }

    void HID::onSetReport(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, const uint8_t *buffer,
                          uint16_t bufsize) {
        dispatchEvent(TUsbSetReportEvent(instance, report_id, report_type, buffer, bufsize));
    }

    void HID::remoteWakeup() const {
        if (getState() == Suspended && isRemoteWakeupEnabled()) {
            tud_remote_wakeup();
        }
    }

    void HID::task() {
        tud_task();
        runNextHidTask();
    }

    bool HID::isHidTaskRunning() const {
        return hidTaskRunning;
    }

    int HID::scheduleHidTasks(std::initializer_list<std::shared_ptr<HIDTask>> va_hidTasks, bool partial) {
        int successCount = 0;

        critical_section_enter_blocking(&hidTaskSection);
        auto remainingSize = HID::hidTasksLimit - hidTasks.size();
        if (remainingSize >= va_hidTasks.size() || partial) {
            for (const auto &hidTask: va_hidTasks) {
                if (hidTasks.size() < HID::hidTasksLimit) {
                    hidTasks.push(hidTask);
                    successCount++;
                }
            }
        }
        critical_section_exit(&hidTaskSection);

        return successCount;
    }

    void HID::runNextHidTask() {
        if (hidTaskRunning || getState() != Mount) {
            return;
        }

        std::shared_ptr<HIDTask> nextHidTask;
        critical_section_enter_blocking(&hidTaskSection);
        if (!hidTasks.empty()) {
            nextHidTask = hidTasks.front();
            hidTasks.pop();
        }
        critical_section_exit(&hidTaskSection);

        if (nextHidTask != nullptr) {
            hidTaskRunning = true;
            nextHidTask->task();
        }
    }

    void tud_mount_cb_HID() {
        HID &hid = HID::getInstance();
        hid.setState(Mount);
    }

    void tud_umount_cb_HID() {
        HID &hid = HID::getInstance();
        hid.setState(Unmount);
    }

    void tud_suspend_cb_HID(bool remote_wakeup_en) {
        HID &hid = HID::getInstance();
        hid.setRemoteWakeupEnabled(remote_wakeup_en);
        hid.setState(Suspended);
    }

    void tud_resume_cb_HID() {
        HID &hid = HID::getInstance();
        hid.setState(Mount);
    }

    uint16_t tud_hid_get_report_cb_HID(uint8_t instance, uint8_t report_id, hid_report_type_t report_type,
                                       uint8_t *buffer, uint16_t reqlen) {
        // TODO not Implemented: tud_hid_get_report_cb
        (void) instance;
        (void) report_id;
        (void) report_type;
        (void) buffer;
        (void) reqlen;

        return 0;
    }

    void tud_hid_report_complete_cb_HID(uint8_t instance, uint8_t const *report, uint8_t len) {
        HID &hid = HID::getInstance();
        hid.onReportCompleted(instance, report, len);
    }

    void tud_hid_set_report_cb_HID(uint8_t instance, uint8_t report_id, hid_report_type_t report_type,
                                   uint8_t const *buffer, uint16_t bufsize) {
        HID &hid = HID::getInstance();
        hid.onSetReport(instance, report_id, report_type, buffer, bufsize);
    }

}

extern "C" {

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

void tud_mount_cb() {
    brunothg_pico_hid::tud_mount_cb_HID();
}

void tud_umount_cb() {
    brunothg_pico_hid::tud_umount_cb_HID();
}

void tud_suspend_cb(bool remote_wakeup_en) {
    brunothg_pico_hid::tud_suspend_cb_HID(remote_wakeup_en);
}

void tud_resume_cb(void) {
    brunothg_pico_hid::tud_resume_cb_HID();
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen) {
    return brunothg_pico_hid::tud_hid_get_report_cb_HID(instance, report_id, report_type, buffer, reqlen);
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint8_t len) {
    brunothg_pico_hid::tud_hid_report_complete_cb_HID(instance, report, len);
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer,
                           uint16_t bufsize) {
    brunothg_pico_hid::tud_hid_set_report_cb_HID(instance, report_id, report_type, buffer, bufsize);
}

}
