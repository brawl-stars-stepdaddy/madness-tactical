#include "TimerProjectile.hpp"
#include "ExplosionEntity.hpp"
#include "World.hpp"
#include "EventManager.hpp"
#include "DestructionEventData.hpp"

TimerProjectile::TimerProjectile(
        World *world,
        sf::Vector2f center,
        sf::Vector2f impulse,
        float radius,
        float explosion_radius,
        float activation_time,
        float explosion_time
) :   Projectile(world, center, impulse, radius, explosion_radius),
      m_activation_timer(activation_time),
      m_explosion_timer(explosion_time) {}

void TimerProjectile::explode() {
    if (m_explosion_timer <= 0 && !is_exploded) {
        m_world->add_entity(std::make_unique<ExplosionEntity>(
                m_world,
                Explosion({m_body.get_position().x, m_body.get_position().y}, explosion_radius))
        );
        is_exploded = true;
        m_body.get_b2Body()->SetEnabled(false);
        EventManager::get()->queue_event(std::make_unique<DestructionEventData>(this));
    }
}

void TimerProjectile::update_current(sf::Time delta_time) {
    m_activation_timer -= delta_time.asSeconds();
    if (m_activation_timer <= 0) {
        m_explosion_timer -= delta_time.asSeconds();
    }
    explode();
    setPosition(
            {m_body.get_position().x * World::SCALE,
             m_body.get_position().y * World::SCALE}
    );
    setRotation(m_body.get_rotation() * 60);
}

void TimerProjectile::on_collision(Entity *) {
    explode();
}
