#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "EntityType.hpp"
#include "game_objects/SceneNode.hpp"

struct Explosion;
struct Body;
struct World;

struct Entity : SceneNode {
public:
    explicit Entity(World &world);

    virtual Body &get_body() = 0;
    virtual EntityType get_type() = 0;

    virtual void on_collision(std::shared_ptr<Entity> other_object) = 0;
    virtual void on_explosion(const Explosion &explosion) = 0;

protected:
    void update_current(sf::Time delta_time) override;
};

#endif // ENTITY_HPP_