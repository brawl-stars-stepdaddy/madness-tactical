#include "MoveTransitionEventData.hpp"

MoveTransitionEventData::MoveTransitionEventData(TransitionType transition_type)
    : m_transition_type(transition_type) {
}

EventType MoveTransitionEventData::get_event_type() const {
    return EventType::MOVE_TRANSITION;
}

MoveTransitionEventData::TransitionType
MoveTransitionEventData::get_transition_type() const {
    return m_transition_type;
}