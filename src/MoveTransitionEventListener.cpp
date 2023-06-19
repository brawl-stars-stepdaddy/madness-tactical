#include "MoveTransitionEventListener.hpp"
#include <cassert>
#include "World.hpp"

MoveTransitionEventListener::MoveTransitionEventListener(World *world)
    : m_world(world) {
}

void MoveTransitionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::MOVE_TRANSITION);
    auto move_transition_event =
        static_cast<const MoveTransitionEventData &>(event);
    switch (move_transition_event.get_transition_type()) {
        case MoveTransitionEventData::TransitionType::OTHER_UNIT:
            m_world->go_to_next_unit();
            break;
        case MoveTransitionEventData::TransitionType::OTHER_PLAYER:
            m_world->go_to_next_team();
            break;
    }
}
