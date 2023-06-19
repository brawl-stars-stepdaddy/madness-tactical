#include "ExplosionEntity.hpp"
#include "DestructionEventData.hpp"
#include "EventManager.hpp"
#include "ExplosionEventData.hpp"
#include "World.hpp"

ExplosionEntity::ExplosionEntity(World &world, Explosion explosion)
    : Entity(world),
      m_explosion(explosion),
      m_body(
          this,
          m_world->get_physics_world(),
          {explosion.get_coordinates().first,
           explosion.get_coordinates().second},
          explosion.get_radius(),
          true,
          false
      ) {
}

void ExplosionEntity::on_collision(Entity *other_object) {
    if (other_object->get_type() != EntityType::EXPLOSION &&
        other_object->get_type() != EntityType::PROJECTILE) {
        m_world->get_event_manager()->queue_event(
            std::make_unique<ExplosionEventData>(m_explosion, other_object)
        );
    }
    m_body.get_b2Body()->SetEnabled(false);
    m_world->get_event_manager()->queue_event(
        std::make_unique<DestructionEventData>(this)
    );
}

EntityType ExplosionEntity::get_type() {
    return EntityType::EXPLOSION;
}

Body &ExplosionEntity::get_body() {
    return m_body;
}
