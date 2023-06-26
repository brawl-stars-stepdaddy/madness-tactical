#ifndef EXPLOSION_ENTITY_HPP_
#define EXPLOSION_ENTITY_HPP_

#include "Entity.hpp"
#include "game_objects/bodies/CircleBody.hpp"
#include "utils/Explosion.hpp"

struct World;

struct ExplosionEntity : Entity {
public:
    ExplosionEntity(World &world, Explosion explosion);

    EntityType get_type() override;
    Body &get_body() override;

    void on_explosion(const Explosion &explosion) override {};
    void on_collision(std::shared_ptr<Entity> other_object) override;

private:
    Explosion m_explosion;
    CircleBody m_body;
};

#endif  // EXPLOSION_ENTITY_HPP_
