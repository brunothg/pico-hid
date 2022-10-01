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

#include "EventDispatcher.h"

#include <algorithm>

namespace brunothg_pico_hid {

    EventDispatcher::~EventDispatcher() {
        std::vector<EventListener *> tmpListeners(listeners);
        listeners.clear();
        for (auto listener: tmpListeners) {
            removeEventListener(listener);
        }
    }

    void EventDispatcher::addEventListener(EventListener *listener) {
        listeners.push_back(listener);

        auto &dispatchers = listener->dispatchers;
        dispatchers.push_back(this);
    }

    void EventDispatcher::removeEventListener(EventListener *listener) {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());

        auto &dispatchers = listener->dispatchers;
        dispatchers.erase(std::remove(dispatchers.begin(), dispatchers.end(), this), dispatchers.end());
    }

    void EventDispatcher::dispatchEvent(const Event &event) const {
        for (auto listener: listeners) {
            try {
                listener->onEvent(event);
            } catch (...) {}
        }
    }
}
