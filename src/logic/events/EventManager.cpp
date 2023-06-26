#include <algorithm>
#include "logic/events/EventManager.hpp"

EventManager::EventManager() = default;

bool EventManager::add_listener(
    EventListenerPtr event_listener,
    const EventType &type
) {
    EventListenerList &event_listener_list = m_event_listeners[type];
    event_listener_list.push_back(std::move(event_listener));
    return true;
}

bool EventManager::remove_listener(
    const EventListener &event_listener,
    const EventType &type
) {
    EventListenerList &event_listener_list = m_event_listeners[type];
    auto found = std::find_if(
        event_listener_list.begin(), event_listener_list.end(),
        [&event_listener](const EventListenerPtr &ptr) {
            return ptr.get() == &event_listener;
        }
    );
    if (found == event_listener_list.end()) {
        return false;
    }
    event_listener_list.erase(found);
    return true;
}

bool EventManager::trigger_event(std::unique_ptr<EventData> event) const {
    bool processed = false;
    auto found = m_event_listeners.find(event->get_event_type());
    if (found != m_event_listeners.end()) {
        const EventListenerList &event_listener_list = found->second;
        for (auto &event_listener : event_listener_list) {
            event_listener->process(*event);
            processed = true;
        }
    }
    return processed;
}

bool EventManager::queue_event(std::unique_ptr<EventData> event) {
    auto found = m_event_listeners.find(event->get_event_type());
    if (found == m_event_listeners.end()) {
        return false;
    }
    m_queues[m_current_queue].push_back(std::move(event));
    return true;
}

bool EventManager::update() {
    int queue_to_process = m_current_queue;
    m_current_queue ^= 1;
    while (!m_queues[queue_to_process].empty()) {
        const EventData &event = *m_queues[queue_to_process].front();
        auto found = m_event_listeners.find(event.get_event_type());
        if (found != m_event_listeners.end()) {
            const EventListenerList &event_listener_list = found->second;
            for (auto &event_listener : event_listener_list) {
                event_listener->process(event);
            }
        }
        m_queues[queue_to_process].pop_front();
    }
    return true;
}
