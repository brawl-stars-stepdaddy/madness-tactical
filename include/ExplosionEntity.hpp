#ifndef EXPLOSION_ENTITY_HPP_
#define EXPLOSION_ENTITY_HPP_

#include "CircleBody.hpp"
#include "Entity.hpp"
#include "Explosion.hpp"

struct World;

struct ExplosionEntity : Entity {
public:
    ExplosionEntity(World &world, Explosion);
    EntityType get_type() override;
    Body &get_body() override;
    void on_explosion(const Explosion &) override{};
    void on_collision(Entity *) override;

private:
    Explosion m_explosion;
    CircleBody m_body;
};

#endif  // EXPLOSION_ENTITY_HPP_
