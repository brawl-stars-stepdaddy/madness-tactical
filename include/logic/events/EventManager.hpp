#ifndef EVENT_MANAGER_HPP_
#define EVENT_MANAGER_HPP_

#include <list>
#include <map>
#include <memory>
#include "EventType.hpp"
#include "logic/events/event_listeners/EventListener.hpp"

struct EventManager {
public:
    typedef std::unique_ptr<EventListener> EventListenerPtr;
    typedef std::unique_ptr<EventData> EventDataPtr;

    EventManager();

    bool add_listener(EventListenerPtr event_listener, const EventType &type);

    bool remove_listener(const EventListener &event_listener, const EventType &type);

    [[nodiscard]] bool trigger_event(EventDataPtr event) const;

    bool queue_event(EventDataPtr event);

    bool update();

private:
    typedef std::list<std::unique_ptr<EventListener>> EventListenerList;
    typedef std::map<EventType, EventListenerList> EventListenerMap;
    typedef std::list<std::unique_ptr<EventData>> EventQueue;

    EventListenerMap m_event_listeners;
    EventQueue m_queues[2];
    int m_current_queue = 0;
};

#endif // EVENT_MANAGER_HPP_
