#ifndef MAP_HPP_
#define MAP_HPP_

#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include "Entity.hpp"
#include "game_objects/bodies/MapBody.hpp"

struct Explosion;
struct World;

struct Map : Entity {
public:
    explicit Map(World &world,
                 const std::vector<std::vector<std::pair<float, float>>> &chains
                 );

    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update_current(sf::Time delta_time) override;

    MapBody &get_body() override;

    EntityType get_type() override;

    void on_collision(std::shared_ptr<Entity> other_object) override;
    void on_explosion(const Explosion &explosion) override;

private:
    MapBody m_body;
    std::vector<sf::ConvexShape> m_sprites;
    std::vector<sf::CircleShape> m_explosions;
};

#endif // MAP_HPP_