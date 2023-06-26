#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "Entity.hpp"
#include "game_objects/bodies/CircleBody.hpp"
#include "utils/ResourceIdentifiers.hpp"

struct World;

struct Projectile : Entity {
public:
    Projectile(World &world,
               sf::Vector2f center,
               sf::Vector2f impulse,
               float radius,
               float explosion_radius,
               bool is_sensor,
               bool is_static,
               TexturesID texture
               );

    CircleBody &get_body() override;
    EntityType get_type() override;

    void on_collision(std::shared_ptr<Entity> other_object) override;
    void on_explosion(const Explosion &explosion) override;

protected:
    void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    CircleBody m_body;

    bool m_is_exploded = false;
    float m_explosion_radius;
};

#endif  // PROJECTILE_HPP_
