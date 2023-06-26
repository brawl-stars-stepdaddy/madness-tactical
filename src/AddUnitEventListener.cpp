#include "AddUnitEventListener.hpp"
#include "World.hpp"

AddUnitEventListener::AddUnitEventListener(World &world) : m_world(&world) {}

void AddUnitEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::ADD_UNIT);
    auto add_unit_event = static_cast<const AddUnitEventData &>(event);
    m_world->create_unit();
}
