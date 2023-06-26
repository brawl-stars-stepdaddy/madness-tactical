#ifndef COLLISION_PROJECTILE_HPP_
#define COLLISION_PROJECTILE_HPP_

#include "Projectile.hpp"

struct CollisionProjectile : Projectile {
public:
    CollisionProjectile(World &world,
                        sf::Vector2f center,
                        sf::Vector2f impulse,
                        float radius,
                        float explosion_radius,
                        bool is_sensor,
                        bool is_static,
                        TexturesID texture
                        );

    void on_collision(std::shared_ptr<Entity> other_object) override;
};

#endif  // COLLISION_PROJECTILE_HPP_
