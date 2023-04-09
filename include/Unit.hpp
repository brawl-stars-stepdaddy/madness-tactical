#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "CircleBody.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "World.hpp"

struct Unit : Entity {
public:
    enum class Type {
        ENGINEER,
        WORM,
    };

    Unit(std::nullptr_t);
    Unit(Type type, World &world, sf::Vector2f, float);

    CircleBody &get_body() override;

private:
    void draw_current(sf::RenderTarget &target, sf::RenderStates)
        const override;

    void update_current(sf::Time delta_time) override;

    sf::Sprite m_sprite;
    Type m_type;
    CircleBody m_body;
};

#endif