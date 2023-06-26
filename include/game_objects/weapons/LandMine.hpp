#ifndef LAND_MINE_HPP_
#define LAND_MINE_HPP_

#include "Weapon.hpp"

struct LandMine : Weapon {
public:
    LandMine(World &world, Unit *parent);

    void launch() override;
    WeaponControllerType get_controller_type() override;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

    float m_projectile_radius = 0.5f;
    float m_explosion_radius = 3.0f;
    float m_activation_time = 5.0f;
    float m_explosion_time = 1.0f;

    sf::Sprite m_sprite;
};

#endif  // LAND_MINE_HPP_
