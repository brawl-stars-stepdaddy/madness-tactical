#include "Entity.hpp"

void Entity::update_current(sf::Time delta_time) {
    setPosition({get_body().get_position().x * 100, get_body().get_position().y * 100});
    setRotation(get_body().get_rotation());
}