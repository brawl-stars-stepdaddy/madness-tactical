#ifndef EVENT_LISTENER_HPP_
#define EVENT_LISTENER_HPP_

#include "logic/events/event_data/EventData.hpp"

struct EventListener {
public:
    virtual void process(const EventData &event) = 0;

    virtual ~EventListener() = default;
};

#endif // EVENT_LISTENER_HPP_
