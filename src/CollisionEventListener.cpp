#include "CollisionEventListener.hpp"

void CollisionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::COLLISION);
    auto collision_event = static_cast<const CollisionEventData &>(event);
    collision_event.get_first_object()->on_collision(collision_event.get_second_object());
    collision_event.get_second_object()->on_collision(collision_event.get_first_object());
}

