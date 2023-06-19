#include "TimerProjectile.hpp"
#include "ExplosionEntity.hpp"
#include "World.hpp"
#include "DestructionEventData.hpp"

TimerProjectile::TimerProjectile(
        World &world,
        sf::Vector2f center,
        sf::Vector2f impulse,
        float radius,
        float explosion_radius,
        float activation_time,
        float explosion_time,
        bool is_sensor,
        bool is_static,
        TexturesID texture
) :   Projectile(world, center, impulse, radius, explosion_radius, is_sensor, is_static, texture),
      m_activation_timer(activation_time),
      m_explosion_timer(explosion_time) {}

void TimerProjectile::explode() {
    if (m_explosion_timer <= 0 && !is_exploded) {
        m_world->add_entity(std::make_unique<ExplosionEntity>(
                *m_world,
                Explosion({m_body.get_position().x, m_body.get_position().y}, explosion_radius))
        );
        is_exploded = true;
        m_body.get_b2Body()->SetEnabled(false);
        m_world->get_event_manager()->queue_event(std::make_unique<DestructionEventData>(this));
    }
}

void TimerProjectile::update_current(sf::Time delta_time) {
    Projectile::update_current(delta_time);
    m_activation_timer -= delta_time.asSeconds();
    if (is_activated) {
        m_explosion_timer -= delta_time.asSeconds();
    }
    explode();
}

void TimerProjectile::on_collision(Entity *) {
    if (m_activation_timer <= 0) {
        is_activated = true;
    }
    explode();
}
