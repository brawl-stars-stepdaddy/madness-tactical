#include "Unit.hpp"
#include <iostream>
#include "ResourceHolder.hpp"

TexturesID to_texture_id(Unit::Type type) {
    switch (type) {
        case Unit::Type::ENGINEER:
            return TexturesID::ENGINEER;
        case Unit::Type::WORM:
            return TexturesID::WORM;
        default:
            throw std::runtime_error("to_texture_id - failed to map Unit::Type"
            );
    }
}

Unit::Unit(Unit::Type type, World &world, sf::Vector2f center, float radius)
    : m_type(type),
      m_sprite(world.get_texture_holder().get(to_texture_id(type))),
      m_body(UnitBody(this, world.get_physics_world(), center, radius)) {
    m_sprite.setScale(
        radius * World::SCALE * 2 / m_sprite.getLocalBounds().width,
        radius * World::SCALE * 2 / m_sprite.getLocalBounds().height
    );
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Unit::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void Unit::update_current(sf::Time delta_time) {
    setPosition(
        {m_body.get_position().x * World::SCALE,
         m_body.get_position().y * World::SCALE}
    );
    setRotation(m_body.get_rotation() * 60);
}

UnitBody &Unit::get_body() {
    return m_body;
}

EntityType Unit::get_type() {
    return EntityType::UNIT;
}

void Unit::on_collision(Entity *) {}

void Unit::on_explosion(const Explosion &) {}
