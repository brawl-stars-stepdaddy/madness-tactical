#ifndef EVENT_DATA_HPP
#define EVENT_DATA_HPP

#include <SFML/Graphics.hpp>
#include <ostream>
#include "EventType.hpp"

struct EventData {
public:
    [[nodiscard]] virtual EventType get_event_type() const = 0;

    // virtual void serialize(std::ostream &out) const = 0;

    // virtual EventData *copy() const = 0;

    // virtual std::string get_name() const = 0;

    virtual ~EventData() = default;
};

#endif
