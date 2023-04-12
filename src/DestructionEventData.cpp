#include "DestructionEventData.hpp"

DestructionEventData::DestructionEventData(SceneNode *object) : m_object(object) {}

EventType DestructionEventData::get_event_type() const {
    return EventType::DESTRUCTION;
}

SceneNode *DestructionEventData::get_object() const {
    return m_object;
}
