#ifndef CIRCLE_BODY_HPP_
#define CIRCLE_BODY_HPP_

#include "Body.hpp"
#include "box2d/box2d.h"

struct CircleBody : Body {
public:
    CircleBody(b2World &world, sf::Vector2f center, float radius);
    sf::Vector2f get_position() override;
    float get_rotation() override;
};

#endif // CIRCLE_BODY_HPP_
