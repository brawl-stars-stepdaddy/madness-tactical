#ifndef BODY_HPP_
#define BODY_HPP_

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

struct Body {
public:
    virtual sf::Vector2f get_position() = 0;
    virtual float get_rotation() = 0;
};

#endif