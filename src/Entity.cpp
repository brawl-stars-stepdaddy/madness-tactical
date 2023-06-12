#include "Entity.hpp"
#include "Body.hpp"
#include "World.hpp"

Entity::Entity(World &world) : SceneNode(world) {

}

void Entity::update_current([[maybe_unused]] sf::Time delta_time) {
    setPosition(
        {get_body().get_position().x * World::SCALE, get_body().get_position().y * World::SCALE}
    );
    setRotation(get_body().get_rotation());
}
