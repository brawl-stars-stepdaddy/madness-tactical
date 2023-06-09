#ifndef COLLISION_PROJECTILE_HPP_
#define COLLISION_PROJECTILE_HPP_

#include "Projectile.hpp"

struct CollisionProjectile : Projectile {

    CollisionProjectile(World *, sf::Vector2f, sf::Vector2f, float, float);

    void on_collision(Entity *) override;

};

#endif // COLLISION_PROJECTILE_HPP_
