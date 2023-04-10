#include "CollisionEventListener.hpp"

CollisionEventListener::CollisionEventListener(World *world) {
    m_contact_listener = ContactListener();
    world->get_physics_world().SetContactListener(&m_contact_listener);
}

void CollisionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::COLLISION);
    auto collision_event = static_cast<const CollisionEventData &>(event);
    collision_event.get_first_object()->on_collision(collision_event.get_second_object());
    collision_event.get_second_object()->on_collision(collision_event.get_first_object());
}

