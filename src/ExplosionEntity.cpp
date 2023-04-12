#include "ExplosionEntity.hpp"
#include "World.hpp"
#include "EventManager.hpp"
#include "ExplosionEventData.hpp"
#include "DestructionEventData.hpp"

ExplosionEntity::ExplosionEntity(World *world, Explosion explosion)
    : m_explosion(explosion),
      m_body(this, world->get_physics_world(),
             {explosion.get_coordinates().first, explosion.get_coordinates().second},
             explosion.get_radius(), true) {
}

void ExplosionEntity::on_collision(Entity *other_object) {
    EventManager::get()->queue_event(
            std::make_unique<ExplosionEventData>(m_explosion, other_object)
    );
    m_body.get_b2Body()->SetEnabled(false);
    EventManager::get()->queue_event(std::make_unique<DestructionEventData>(this));
}

EntityType ExplosionEntity::get_type() {
    return EntityType::EXPLOSION;
}

Body &ExplosionEntity::get_body() {
    return m_body;
}
