#ifndef KETTLEBELL_PROJECTILE_HPP_
#define KETTLEBELL_PROJECTILE_HPP_

#include "Projectile.hpp"

struct KettlebellProjectile : Projectile {
    KettlebellProjectile(World &, sf::Vector2f, float, float, TexturesID);

    void on_collision(std::shared_ptr<Entity>) override;

private:
    void update_current(sf::Time delta_time) override;
    float m_radius;
};

#endif  // KETTLEBELL_PROJECTILE_HPP_
