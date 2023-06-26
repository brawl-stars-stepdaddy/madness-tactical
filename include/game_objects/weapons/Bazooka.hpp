#ifndef BAZOOKA_HPP_
#define BAZOOKA_HPP_

#include "ChargeableWeapon.hpp"

struct Bazooka : ChargeableWeapon {
public:
    Bazooka(World &world, Unit *parent);

    void launch() override;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

    float m_projectile_radius = 0.5f;
    float m_explosion_radius = 3.0f;

    sf::Sprite m_sprite;
};

#endif  // BAZOOKA_HPP_
