#ifndef EXPLOSION_ENTITY_HPP_
#define EXPLOSION_ENTITY_HPP_

#include "Entity.hpp"
#include "CircleBody.hpp"

struct World;

struct ExplosionEntity : Entity {
public:
    ExplosionEntity(World *, Explosion);
    EntityType get_type() override;
    Body &get_body() override;
    void on_explosion(const Explosion &) override {};
    void on_collision(Entity *) override;

private:
    CircleBody m_body;
    Explosion m_explosion;
};

#endif // EXPLOSION_ENTITY_HPP_
