#include "Entity.hpp"

void Entity::update_current(sf::Time delta_time) {
    m_relative_transform.setPosition(m_body.get_position());
    m_relative_transform.setRotation(m_body.get_rotation());
}