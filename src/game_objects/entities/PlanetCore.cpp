#include "game_objects/entities/PlanetCore.hpp"
#include "game_objects/entities/Box.hpp"
#include "game_objects/entities/Unit.hpp"
#include "logic/World.hpp"
#include "logic/events/event_data/DestructionEventData.hpp"
#include "utils/ResourceHolder.hpp"

PlanetCore::PlanetCore(World &world, float radius)
    : Entity(world),
      m_sprite(m_world->get_texture_holder().get(TexturesID::PLANET_CORE)),
      m_body(CircleBody(
          this,
          m_world->get_physics_world(),
          {0, 0},
          radius,
          false,
          true
      )) {
    m_sprite.setScale(
        static_cast<float>(radius * World::SCALE * 2.1 / m_sprite.getLocalBounds().width),
        static_cast<float>(radius * World::SCALE * 2.1 / m_sprite.getLocalBounds().height)
    );
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void PlanetCore::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void PlanetCore::update_current(sf::Time delta_time) {
    Entity::update_current(delta_time);
}

CircleBody &PlanetCore::get_body() {
    return m_body;
}

EntityType PlanetCore::get_type() {
    return EntityType::PLANET_CORE;
}

void PlanetCore::on_collision(std::shared_ptr<Entity> other_object) {
    if (other_object->get_type() == EntityType::UNIT) {
        auto unit = std::static_pointer_cast<Unit>(other_object);
        unit->change_health(-unit->get_health());
    }
    if (other_object->get_type() == EntityType::BOX) {
        auto box = std::static_pointer_cast<Box>(other_object);
        box->detach();
    }
}

void PlanetCore::on_explosion(const Explosion &) {
}
