#ifndef MADNESS_TACTICAL_RECTBODY_HPP
#define MADNESS_TACTICAL_RECTBODY_HPP

#include "Body.hpp"
#include "box2d/box2d.h"

struct CircleBody : Body {
public:
    CircleBody();
    CircleBody(b2World &world, sf::Vector2f center, float radius);
    sf::Vector2f get_position() override;
    float get_rotation() override;

    b2Body *get_b2Body() override {
        return m_body;
    }

private:
    b2BodyDef m_body_def;
    b2Body *m_body = nullptr;
    b2CircleShape m_circle_shape;
    b2FixtureDef m_fixture_def;
};

#endif
