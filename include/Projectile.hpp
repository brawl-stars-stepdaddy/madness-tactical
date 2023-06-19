#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "CircleBody.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

struct World;

struct Projectile : Entity {
    Projectile(World &, sf::Vector2f, sf::Vector2f, float, float, bool, bool, TexturesID);

    CircleBody &get_body() override;
    EntityType get_type() override;

    void on_collision(Entity *) override;
    void on_explosion(const Explosion &) override;

protected:
    void draw_current(sf::RenderTarget &target, sf::RenderStates) const override;
    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    CircleBody m_body;
    bool is_exploded = false;
    float explosion_radius;
};

#endif  // PROJECTILE_HPP_
