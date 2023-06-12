#include "Entity.hpp"
#include "Body.hpp"
#include "World.hpp"

Entity::Entity(World &world) : SceneNode(world) {

}

void Entity::update_current([[maybe_unused]] sf::Time delta_time) {
    auto [x, y] = get_body().get_position();
    float gravitation_rotation = atan2(x, y);
    setPosition(
        {x * World::SCALE, y * World::SCALE}
    );
    setRotation(-(get_body().get_rotation() + gravitation_rotation + M_PI) * (180.0f / M_PI));

    b2Body *body = get_body().get_b2Body();
    float mass = body->GetMass();
    b2Vec2 direction = body->GetPosition();
    float distance_squared = direction.LengthSquared();
    direction.Normalize();

    distance_squared = std::max(10.f, distance_squared);

    direction *= -10000 * mass / distance_squared;
    body->ApplyForceToCenter(direction, false);
}
