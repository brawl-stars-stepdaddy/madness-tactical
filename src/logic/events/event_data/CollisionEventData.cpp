#include "logic/events/event_data/CollisionEventData.hpp"

CollisionEventData::CollisionEventData(
    std::shared_ptr<Entity> first_object,
    std::shared_ptr<Entity> second_object,
    CollisionType collision_type
)
    : m_first_object(std::move(first_object)),
      m_second_object(std::move(second_object)),
      m_collision_type(collision_type) {
}

EventType CollisionEventData::get_event_type() const {
    return EventType::COLLISION;
}

CollisionEventData::CollisionType CollisionEventData::get_collision_type(
) const {
    return m_collision_type;
}

std::shared_ptr<Entity> CollisionEventData::get_first_object() const {
    return m_first_object;
}

std::shared_ptr<Entity> CollisionEventData::get_second_object() const {
    return m_second_object;
}
