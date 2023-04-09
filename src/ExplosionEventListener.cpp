#include "ExplosionEventListener.hpp"

ExplosionEventListener::ExplosionEventListener(World *world) {
    m_world = world;
}

void ExplosionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::EXPLOSION);
    auto explosion_event = static_cast<const ExplosionEventData &>(event);
    m_world->get_map()->apply_explosion(explosion_event.get_explosion());
}
