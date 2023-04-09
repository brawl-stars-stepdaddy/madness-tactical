#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include "EventData.hpp"

struct EventListener {
public:
    virtual void process(const EventData &event) = 0;

    virtual ~EventListener() = default;
};

#endif
