#include <iostream>
#include "Unit.hpp"
#include "ResourceHolder.hpp"

TexturesID to_texture_id(Unit::Type type) {
    switch (type) {
        case Unit::Type::ENGINEER:
            return TexturesID::ENGINEER;
        default:
            throw std::runtime_error("to_texture_id - failed to map Unit::Type"
            );
    }
}

Unit::Unit(std::nullptr_t) {
}

Unit::Unit(Unit::Type type, World &world, const TextureHolder &textureHolder)
    : m_type(type), m_sprite(textureHolder.get(to_texture_id(type))) {
    m_body = RectBody(world.get_physics_world(), sf::FloatRect(0, 0, 1, 1));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Unit::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void Unit::update_current(sf::Time delta_time) {
    setPosition({m_body.get_position().x * 100, m_body.get_position().y * 100});
    setRotation(m_body.get_rotation());
}

RectBody &Unit::get_body() {
    return m_body;
}
