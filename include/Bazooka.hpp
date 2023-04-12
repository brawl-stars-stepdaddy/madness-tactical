#ifndef BAZOOKA_HPP_
#define BAZOOKA_HPP_

#include "Weapon.hpp"

struct Bazooka : Weapon {
public:
    explicit Bazooka(World *, Unit *);

    void charge(sf::Time) override;
    void change_angle(sf::Time, float) override;
    void launch(World &) override;

protected:
    void reset() override;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const override;

    float m_angle = 0.0f;
    float m_charge_level = 0.1f;
    float m_projectile_radius = 0.5f;
    float m_explosion_radius = 3.0f;

    sf::Sprite m_sprite;
};

#endif  // BAZOOKA_HPP_
