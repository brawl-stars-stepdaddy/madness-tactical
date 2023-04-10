#ifndef MADNESS_TACTICAL_RECTBODY_HPP
#define MADNESS_TACTICAL_RECTBODY_HPP

#include "Body.hpp"
#include "box2d/box2d.h"

struct Entity;

struct RectBody : Body {
public:
    RectBody();
    RectBody(Entity *, b2World &world, sf::FloatRect);
    sf::Vector2f get_position() override;
    float get_rotation() override;
};

#endif
