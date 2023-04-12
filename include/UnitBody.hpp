#ifndef UNIT_BODY_HPP_
#define UNIT_BODY_HPP_

#include "Body.hpp"
#include "box2d/box2d.h"

struct Unit;

struct UnitBody : Body {
public:
    UnitBody(Unit *, b2World &world, sf::Vector2f center, float radius);
    sf::Vector2f get_position() override;
    float get_rotation() override;
};

#endif  // UNIT_BODY_HPP_
