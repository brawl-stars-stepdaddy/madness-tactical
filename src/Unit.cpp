#include "Unit.hpp"
#include "ResourceHolder.hpp"

TexturesID to_texture_id(Unit::Type type) {
    switch (type) {
        case Unit::Type::ENGINEER:
            return TexturesID::ENGINEER;
        default:
            throw std::runtime_error("to_texture_id - failed to map Unit::Type");
    }
}

Unit::Unit(Unit::Type type, const TextureHolder &textureHolder) : m_type(type), m_sprite(textureHolder.get(
        to_texture_id(type))) {
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Unit::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= m_local_transform.getTransform();
    target.draw(m_sprite, states);
}