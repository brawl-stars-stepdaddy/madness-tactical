#ifndef KETTLEBELL_HPP_
#define KETTLEBELL_HPP_

#include "Weapon.hpp"

struct Kettlebell : Weapon {
public:
    Kettlebell(World &world, Unit *parent);

    void launch() override;
    WeaponControllerType get_controller_type() override;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;

    float m_projectile_radius = 2.0f;
    float m_explosion_radius = 3.0f;

    sf::Sprite m_sprite;
};

#endif  // KETTLEBELL_HPP_
