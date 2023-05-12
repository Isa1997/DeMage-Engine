#include "precomp.h"

#include "Event/eventlistener.h"

namespace Engine
{
    void EventListener::RegisterCallback(Channel* channel,std::function<void(Event*)> eventCallback)
    {
        m_Tracker[channel] = eventCallback;
    }
}