#include "ExplosionEventData.hpp"
#include <utility>

ExplosionEventData::ExplosionEventData(Explosion explosion, Entity *object)
    : m_explosion(std::move(explosion)),
      m_object(object) {
}