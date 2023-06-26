#include "logic/events/event_data/ExplosionEventData.hpp"

ExplosionEventData::ExplosionEventData(
    Explosion explosion,
    std::shared_ptr<Entity> object
)
    : m_explosion(std::move(explosion)), m_object(std::move(object)) {
}