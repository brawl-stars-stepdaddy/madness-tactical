#ifndef CIRCLE_BODY_HPP_
#define CIRCLE_BODY_HPP_

#include <box2d/box2d.h>
#include "Body.hpp"

struct Entity;

struct CircleBody : Body {
public:
    CircleBody(Entity *parent,
               b2World &world,
               sf::Vector2f center,
               float radius,
               bool is_sensor,
               bool is_static
               );

    [[nodiscard]] sf::Vector2f get_position() const override;
    [[nodiscard]] float get_rotation() const override;
};

#endif  // CIRCLE_BODY_HPP_
