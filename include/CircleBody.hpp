#ifndef CIRCLE_BODY_HPP_
#define CIRCLE_BODY_HPP_

#include "Body.hpp"
#include "box2d/box2d.h"

struct Entity;

struct CircleBody : Body {
public:
    CircleBody(Entity *, b2World &, sf::Vector2f, float, bool=false, bool=false);
    sf::Vector2f get_position() override;
    float get_rotation() override;
};

#endif  // CIRCLE_BODY_HPP_
