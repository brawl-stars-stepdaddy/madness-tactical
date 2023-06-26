#include "ExplosionEventData.hpp"
#include <utility>

ExplosionEventData::ExplosionEventData(Explosion explosion, std::shared_ptr<Entity> object)
    : m_explosion(std::move(explosion)), m_object(object) {
}