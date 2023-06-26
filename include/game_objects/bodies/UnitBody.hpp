#ifndef UNIT_BODY_HPP_
#define UNIT_BODY_HPP_

#include <box2d/box2d.h>
#include "Body.hpp"

struct Unit;

struct UnitBody : Body {
public:
    UnitBody(Unit *parent, b2World &world, sf::Vector2f center, float radius);

    [[nodiscard]] sf::Vector2f get_position() const override;
    [[nodiscard]] float get_rotation() const override;
};

#endif  // UNIT_BODY_HPP_
