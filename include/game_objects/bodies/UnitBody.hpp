#ifndef UNIT_BODY_HPP_
#define UNIT_BODY_HPP_

#include "Body.hpp"
#include "box2d/box2d.h"

struct Unit;

struct UnitBody : Body {
public:
    UnitBody(Unit *, b2World &world, sf::Vector2f center, float radius);
    sf::Vector2f get_position() const override;
    float get_rotation() const override;
};

#endif  // UNIT_BODY_HPP_
