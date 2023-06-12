#ifndef TIMER_PROJECTILE_HPP_
#define TIMER_PROJECTILE_HPP_

#include "Projectile.hpp"

struct TimerProjectile : Projectile {
    TimerProjectile(World &, sf::Vector2f, sf::Vector2f, float, float, float, float);

    void explode();
    void on_collision(Entity *) override;

private:
    void update_current(sf::Time delta_time) override;
    float m_activation_timer = 0;
    float m_explosion_timer = 0;
};

#endif // TIMER_PROJECTILE_HPP_
