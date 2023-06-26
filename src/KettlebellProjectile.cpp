#include "KettlebellProjectile.hpp"
#include "DestructionEventData.hpp"
#include "ExplosionEntity.hpp"
#include "World.hpp"

KettlebellProjectile::KettlebellProjectile(
        World &world,
        sf::Vector2f center,
        float radius,
        float explosion_radius,
        TexturesID texture
) : Projectile(
    world,
    center,
    {0, 0},
    radius,
    explosion_radius,
    false,
    false,
    texture
    ),
    m_radius(radius) {}

void KettlebellProjectile::on_collision(std::shared_ptr<Entity> other_object) {
    if (other_object->get_type() != EntityType::EXPLOSION) {
        m_is_exploded = true;
    }
    if (other_object->get_type() == EntityType::PLANET_CORE) {
        m_body.get_b2Body()->SetEnabled(false);
        m_world->get_event_manager()->queue_event(
                std::make_unique<DestructionEventData>(this)
        );
    }
}

void KettlebellProjectile::update_current(sf::Time delta_time) {
    Projectile::update_current(delta_time);
    if (m_is_exploded) {
        b2Vec2 position = {m_body.get_position().x, m_body.get_position().y};
        float distance = position.Normalize();
        position *= (distance - m_radius);
        m_world->add_entity(std::make_unique<ExplosionEntity>(
                *m_world, Explosion(
                        position,
                        m_explosion_radius
                )
        ));
        m_is_exploded = false;
    }
}

