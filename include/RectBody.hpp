#ifndef MADNESS_TACTICAL_RECTBODY_HPP
#define MADNESS_TACTICAL_RECTBODY_HPP

#include "Body.hpp"
#include "box2d/box2d.h"

struct RectBody : Body {
public:
    RectBody();
    RectBody(b2World &world, sf::FloatRect);
    b2Vec2 get_position() override;
    float get_rotation() override;
    b2Body *get_b2Body() override {
        return m_body;
    }

private:
    b2BodyDef m_body_def;
    b2Body *m_body = nullptr;
    b2PolygonShape m_polygon_shape;
    b2FixtureDef m_fixture_def;
};

#endif
