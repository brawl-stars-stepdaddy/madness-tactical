#ifndef RECT_BODY_HPP_
#define RECT_BODY_HPP_

#include <box2d/box2d.h>
#include "Body.hpp"

struct Entity;

struct RectBody : Body {
public:
    RectBody();
    RectBody(Entity *parent, b2World &world, sf::FloatRect rect);

    [[nodiscard]] sf::Vector2f get_position() const override;
    [[nodiscard]] float get_rotation() const override;
};

#endif // RECT_BODY_HPP_
