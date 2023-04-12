#include "CollisionEventData.hpp"

CollisionEventData::CollisionEventData(
        Entity *first_object,
        Entity *second_object,
        CollisionType collision_type
)
        : m_first_object(first_object), m_second_object(second_object), m_collision_type(collision_type) {
}

EventType CollisionEventData::get_event_type() const {
    return EventType::COLLISION;
}

CollisionEventData::CollisionType CollisionEventData::get_collision_type() const {
    return m_collision_type;
}

Entity *CollisionEventData::get_first_object() const {
    return m_first_object;
}

Entity *CollisionEventData::get_second_object() const {
    return m_second_object;
}
