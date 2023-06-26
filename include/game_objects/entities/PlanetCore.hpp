#ifndef PLANET_CORE_HPP_
#define PLANET_CORE_HPP_

#include "Entity.hpp"
#include "game_objects/bodies/CircleBody.hpp"

struct World;

struct PlanetCore : Entity {
public:
    PlanetCore(World &world, float radius);

    CircleBody &get_body() override;
    EntityType get_type() override;

    void on_collision(std::shared_ptr<Entity> other_object) override;
    void on_explosion(const Explosion &explosion) override;

protected:
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    CircleBody m_body;
};

#endif  // PLANET_CORE_HPP_
