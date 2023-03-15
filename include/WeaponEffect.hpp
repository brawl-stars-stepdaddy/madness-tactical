#ifndef WEAPON_EFFECT_TYPE_HPP_
#define WEAPON_EFFECT_TYPE_HPP_

#include <box2d/box2d.h>

struct WeaponEffect {
public:
    enum class WeaponEffectType {
        Explosion
    };

    WeaponEffect(b2Vec2, float, WeaponEffectType);
    [[nodiscard]] std::pair<float, float> get_coordinates() const;
    [[nodiscard]] float get_radius() const;
    [[nodiscard]] WeaponEffectType get_type() const;

private:
    std::pair<float, float> m_coordinates;
    float m_radius;
    WeaponEffectType m_type;
};

#endif //WEAPON_EFFECT_TYPE_HPP_
