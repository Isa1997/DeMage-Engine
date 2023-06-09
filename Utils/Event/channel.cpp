#include "precomp.h"
#include "Event/channel.h"

#include "Event/event.h"

namespace Engine
{
    void Channel::RegisterListener(EventListener* listener)
    {
        m_Listeners.push_back(listener);
    }

    void Channel::UnregisterListener(EventListener* listener)
    {
        m_Listeners.erase(std::find(m_Listeners.begin(), m_Listeners.end(), listener));
    }
}
