#include "logic/events/event_data/AddUnitEventData.hpp"

EventType AddUnitEventData::get_event_type() const {
    return EventType::ADD_UNIT;
}
