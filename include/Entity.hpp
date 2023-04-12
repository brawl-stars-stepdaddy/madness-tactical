#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "Body.hpp"
#include "EntityType.hpp"
#include "SceneNode.hpp"
#include "Explosion.hpp"

struct Entity : SceneNode {
public:
    virtual Body &get_body() = 0;
    virtual EntityType get_type() = 0;
    virtual void on_collision(Entity *) = 0;
    virtual void on_explosion(const Explosion &) = 0;

private:
    void update_current(sf::Time delta_time) override;
};

#endif