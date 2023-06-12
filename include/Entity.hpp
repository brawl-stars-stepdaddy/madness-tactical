#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "EntityType.hpp"
#include "SceneNode.hpp"

struct Explosion;
struct Body;
struct World;

struct Entity : SceneNode {
public:
    Entity(World &world);
    virtual Body &get_body() = 0;
    virtual EntityType get_type() = 0;
    virtual void on_collision(Entity *) = 0;
    virtual void on_explosion(const Explosion &) = 0;

private:
    void update_current(sf::Time delta_time) override;
};

#endif