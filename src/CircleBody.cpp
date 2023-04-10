#include "CircleBody.hpp"

CircleBody::CircleBody(b2World &world, sf::Vector2f center, float radius) {
    b2BodyDef m_body_def;
    b2CircleShape m_circle_shape;
    b2FixtureDef m_fixture_def;

    m_body_def.position.Set(center.x, center.y);
    m_body_def.type = b2_dynamicBody;
    m_body = world.CreateBody(&m_body_def);
    m_circle_shape.m_radius = radius;
    m_fixture_def.shape = &m_circle_shape;
    m_fixture_def.density = 1;
    m_fixture_def.friction = 0.5;
    m_fixture_def.restitution = 0.5;

    m_body->CreateFixture(&m_fixture_def);
}

sf::Vector2f CircleBody::get_position() {
    b2Vec2 pos = m_body->GetPosition();
    return {pos.x, pos.y};
}

float CircleBody::get_rotation() {
    return m_body->GetAngle();
}

