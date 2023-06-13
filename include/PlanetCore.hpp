#ifndef PLANET_CORE_HPP_
#define PLANET_CORE_HPP_

#include "CircleBody.hpp"
#include "Entity.hpp"

struct World;

struct PlanetCore : Entity {
    PlanetCore(World &, float);

    CircleBody &get_body() override;
    EntityType get_type() override;

    void on_collision(Entity *) override;
    void on_explosion(const Explosion &) override;

protected:
    void draw_current(sf::RenderTarget &target, sf::RenderStates) const override;
    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    CircleBody m_body;
};

#endif  // PLANET_CORE_HPP_
