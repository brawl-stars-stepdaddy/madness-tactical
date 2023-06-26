#include "CollisionEventListener.hpp"
#include "World.hpp"

CollisionEventListener::CollisionEventListener(World &world)
    : m_world(&world), m_contact_listener(ContactListener(world)) {
    m_world->get_physics_world().SetContactListener(&m_contact_listener);
}

void CollisionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::COLLISION);
    auto collision_event = static_cast<const CollisionEventData &>(event);
    auto first = collision_event.get_first_object();
    auto second = collision_event.get_second_object();
    if (processed_collisions.find({first, second}) == processed_collisions.end() &&
            processed_collisions.find({second, first}) == processed_collisions.end()) {
        if (collision_event.get_collision_type() ==
                CollisionEventData::CollisionType::BEGIN_CONTACT) {
            first->on_collision(second);
            second->on_collision(first);
        }
        processed_collisions.insert({first, second});
    }
}

void CollisionEventListener::reset() {
    processed_collisions.clear();
}
