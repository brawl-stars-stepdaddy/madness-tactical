#ifndef ADD_UNIT_EVENT_DATA_HPP_
#define ADD_UNIT_EVENT_DATA_HPP_

#include "EventData.hpp"

struct AddUnitEventData : EventData {
public:
    explicit AddUnitEventData() = default;

    [[nodiscard]] EventType get_event_type() const override;
};

#endif  // ADD_UNIT_EVENT_DATA_HPP_
