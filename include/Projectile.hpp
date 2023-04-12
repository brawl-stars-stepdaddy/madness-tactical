#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "CircleBody.hpp"
#include "DestructionEventData.hpp"
#include "Entity.hpp"
#include "EventManager.hpp"
#include "ExplosionEventData.hpp"
#include "World.hpp"

struct Projectile : Entity {
    Projectile(World *, sf::Vector2f, sf::Vector2f, float, float);

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
    World *m_world;
    bool is_exploded = false;
    float explosion_radius;
};

#endif  // PROJECTILE_HPP_
