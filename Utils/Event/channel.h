#pragma once

#include "Event/eventlistener.h"

namespace Engine
{
    class Event;

    class Channel
    {
    public:
        void RegisterListener(EventListener* listener);
        void UnregisterListener(EventListener* listener);

        template<typename EventType>
        void BroadcastEvent(EventType* e)
        {
            for (EventListener* listener : m_Listeners)
            {
                listener->SendEvent(e);
            }
            delete e;
        }
    private:
            std::vector<EventListener*> m_Listeners;
    };
}