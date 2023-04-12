#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "CircleBody.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "UnitBody.hpp"
#include "World.hpp"

struct Weapon;
struct World;

struct Unit : Entity {
public:
    enum class Type {
        ENGINEER,
        WORM,
    };

    Unit(Type type, World *world, sf::Vector2f, float);

    UnitBody &get_body() override;
    EntityType get_type() override;

    float get_direction() const;

    void set_weapon(Weapon *);
    Weapon *get_weapon() const;

    void on_collision(Entity *) override;
    void on_explosion(const Explosion &) override;

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates)
        const override;

    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    Type m_type;
    UnitBody m_body;
    Weapon *m_weapon;
    float m_direction = 1.0f;
};

#endif