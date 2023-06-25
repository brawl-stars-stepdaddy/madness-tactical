#ifndef BODY_HPP_
#define BODY_HPP_

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

struct Body {
public:
    virtual sf::Vector2f get_position() const = 0;
    virtual float get_rotation() const = 0;
    b2Body *get_b2Body();

protected:
    b2Body *m_body = nullptr;
};

#endif