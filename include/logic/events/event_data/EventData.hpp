#ifndef EVENT_DATA_HPP_
#define EVENT_DATA_HPP_

#include "logic/events/EventType.hpp"

struct EventData {
public:
    [[nodiscard]] virtual EventType get_event_type() const = 0;

    virtual ~EventData() = default;
};

#endif // EVENT_DATA_HPP_
