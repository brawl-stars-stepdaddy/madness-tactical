#ifndef BODY_HPP_
#define BODY_HPP_

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

struct Body {
public:
    virtual b2Vec2 get_position() = 0;
    virtual float get_rotation() = 0;
    virtual b2Body *get_b2Body() = 0;
};

#endif