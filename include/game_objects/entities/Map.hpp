#ifndef MAP_HPP_
#define MAP_HPP_

#include "Entity.hpp"
#include "box2d/box2d.h"
#include "clipper2/clipper.h"
#include "game_objects/bodies/MapBody.hpp"
#include "logic/World.hpp"
#include "utils/Explosion.hpp"

struct World;

struct Map : Entity {
public:
    explicit Map(World &world, const std::vector<std::vector<std::pair<float, float>>> &);

    void draw_current(sf::RenderTarget &, sf::RenderStates) const override;
    void update_current(sf::Time delta_time) override;

    MapBody &get_body() override;

    EntityType get_type() override;

    void on_collision(std::shared_ptr<Entity>) override;
    void on_explosion(const Explosion &) override;

private:
    MapBody m_body;
    std::vector<sf::ConvexShape> m_sprites;
    std::vector<sf::CircleShape> m_explosions;
};

#endif