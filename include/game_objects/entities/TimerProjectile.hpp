#ifndef TIMER_PROJECTILE_HPP_
#define TIMER_PROJECTILE_HPP_

#include "Projectile.hpp"

struct TimerProjectile : Projectile {
public:
    TimerProjectile(World &world,
                    sf::Vector2f center,
                    sf::Vector2f impulse,
                    float radius,
                    float explosion_radius,
                    float activation_time,
                    float explosion_time,
                    bool is_sensor,
                    bool is_static,
                    TexturesID texture
                    );

    void explode();
    void on_collision(std::shared_ptr<Entity> other_object) override;

private:
    void update_current(sf::Time delta_time) override;

    float m_activation_timer = 0;
    float m_explosion_timer = 0;
    bool is_activated = false;
};

#endif  // TIMER_PROJECTILE_HPP_
