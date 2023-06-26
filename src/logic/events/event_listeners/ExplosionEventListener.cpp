#include "logic/events/event_listeners/ExplosionEventListener.hpp"

void ExplosionEventListener::process(const EventData &event) {
    assert(event.get_event_type() == EventType::EXPLOSION);
    auto explosion_event = static_cast<const ExplosionEventData &>(event);
    explosion_event.get_object()->on_explosion(explosion_event.get_explosion());
}
