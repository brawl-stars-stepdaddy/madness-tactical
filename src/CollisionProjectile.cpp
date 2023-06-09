#include "CollisionProjectile.hpp"
#include "ExplosionEntity.hpp"
#include "World.hpp"
#include "EventManager.hpp"
#include "DestructionEventData.hpp"

CollisionProjectile::CollisionProjectile(
        World *world,
        sf::Vector2f center,
        sf::Vector2f impulse,
        float radius,
        float explosion_radius
) : Projectile(world, center, impulse, radius, explosion_radius) {}

void CollisionProjectile::on_collision(Entity *other_object) {
    if (!is_exploded) {
        m_world->add_entity(std::make_unique<ExplosionEntity>(
                m_world,
                Explosion({m_body.get_position().x, m_body.get_position().y}, explosion_radius))
        );
        is_exploded = true;
        m_body.get_b2Body()->SetEnabled(false);
        EventManager::get()->queue_event(std::make_unique<DestructionEventData>(this));
    }
}
