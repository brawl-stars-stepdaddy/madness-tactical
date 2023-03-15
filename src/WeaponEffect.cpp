#include "WeaponEffect.hpp"

WeaponEffect::WeaponEffect(b2Vec2 coordinates_, float radius_, WeaponEffectType type_) :
        m_coordinates(coordinates_.x, coordinates_.y),
        m_radius(radius_),
        m_type(type_) {
}

[[nodiscard]] std::pair<float, float> WeaponEffect::get_coordinates() const {
    return m_coordinates;
}

[[nodiscard]] float WeaponEffect::get_radius() const {
    return m_radius;
}

[[nodiscard]] WeaponEffect::WeaponEffectType WeaponEffect::get_type() const {
    return m_type;
}
