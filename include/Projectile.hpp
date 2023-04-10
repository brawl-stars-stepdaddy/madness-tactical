#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "Entity.hpp"
#include "CircleBody.hpp"

struct Projectile : Entity {
    CircleBody &get_body() override;
    EntityType get_type() override;

    void on_collision(Entity *) override;
    void on_explosion(const Explosion &) override;

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates)
    const override;

    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    CircleBody m_body;
};

#endif // PROJECTILE_HPP_
