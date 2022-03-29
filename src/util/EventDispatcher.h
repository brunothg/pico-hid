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

#ifndef PICO_HID_EVENTDISPATCHER_H
#define PICO_HID_EVENTDISPATCHER_H

#include <vector>
#include "util/EventListener.h"
#include "util/Event.h"

namespace brunothg_pico_hid {

    class EventListener;

    class EventDispatcher {
    private:
        /**
         * The registered listeners
         */
        std::vector<EventListener *> listeners;

    protected:
        /**
         * Dispatches the event to all registered listeners
         * @param event The event that will be dispatched
         */
        void dispatchEvent(const Event &event) const;

    public:
        virtual ~EventDispatcher();

        /**
         * Register listener
         * @param listener The new registered listener
         */
        void addEventListener(EventListener *listener);

        /**
         * Remove registered listener
         * @param listener  The listener to remove
         */
        void removeEventListener(EventListener *listener);
    };

}


#endif //PICO_HID_EVENTDISPATCHER_H
