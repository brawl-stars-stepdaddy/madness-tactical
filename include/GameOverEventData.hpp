#ifndef GAVE_OVER_EVENT_DATA_HPP_
#define GAVE_OVER_EVENT_DATA_HPP_

#include "EventData.hpp"

struct GameOverEventData : EventData {
public:
    [[nodiscard]] EventType get_event_type() const override;
};

#endif // GAVE_OVER_EVENT_DATA_HPP_
