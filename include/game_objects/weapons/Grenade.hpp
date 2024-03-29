#ifndef GRENADE_HPP_
#define GRENADE_HPP_

#include "ChargeableWeapon.hpp"

struct Grenade : ChargeableWeapon {
public:
    explicit Grenade(World &world, Unit *parent);

    void launch() override;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

    float m_projectile_radius = 1.0f;
    float m_explosion_radius = 3.0f;
    float m_explosion_time = 3.0f;

    sf::Sprite m_sprite;
};

#endif  // GRENADE_HPP_
