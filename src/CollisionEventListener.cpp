#include "CollisionEventListener.hpp"
#include "World.hpp"

CollisionEventListener::CollisionEventListener(World &world)
    : m_world(&world), m_contact_listener(ContactListener(world)) {
    m_world->get_physics_world().SetContactListener(&m_contact_listener);
}

void CollisionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::COLLISION);
    auto collision_event = static_cast<const CollisionEventData &>(event);
    if (processed_collisions.find(
            {collision_event.get_first_object(),
             collision_event.get_second_object()}
        ) == processed_collisions.end() &&
        processed_collisions.find(
            {collision_event.get_second_object(),
             collision_event.get_first_object()}
        ) == processed_collisions.end()) {
        if (collision_event.get_collision_type() ==
            CollisionEventData::CollisionType::BEGIN_CONTACT) {
            collision_event.get_first_object()->on_collision(
                collision_event.get_second_object()
            );
            collision_event.get_second_object()->on_collision(
                collision_event.get_first_object()
            );
        } else {
            if (collision_event.get_first_object()->get_type() ==
                EntityType::JUMP_SENSOR) {
                static_cast<JumpSensor *>(collision_event.get_first_object())
                    ->end_collision(collision_event.get_second_object());
            }
            if (collision_event.get_second_object()->get_type() ==
                EntityType::JUMP_SENSOR) {
                static_cast<JumpSensor *>(collision_event.get_second_object())
                    ->end_collision(collision_event.get_first_object());
            }
        }
        processed_collisions.insert(
            {collision_event.get_first_object(),
             collision_event.get_second_object()}
        );
    }
}

void CollisionEventListener::reset() {
    processed_collisions.clear();
}
