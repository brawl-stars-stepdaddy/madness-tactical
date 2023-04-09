#include "ExplosionEventData.hpp"
#include <utility>

ExplosionEventData::ExplosionEventData(Explosion explosion)
    : m_explosion(std::move(explosion)) {
}