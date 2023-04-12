#ifndef BAZOOKA_HPP_
#define BAZOOKA_HPP_

#include "Weapon.hpp"

struct Bazooka : Weapon {
    explicit Bazooka(Unit *);

    void charge(sf::Time) override;
    void change_angle(sf::Time, bool) override;
    std::unique_ptr<Projectile> launch(World &) override;

private:
    float m_angle = 0.0f;
    float m_charge_level = 1.0f;
    float m_projectile_radius = 0.5f;
    float m_explosion_radius = 2.0f;
};

#endif  // BAZOOKA_HPP_
