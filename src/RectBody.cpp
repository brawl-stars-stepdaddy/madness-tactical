#include "RectBody.hpp"

RectBody::RectBody() {}

RectBody::RectBody(b2World &world, sf::FloatRect rect) {
    m_body_def.position.Set(rect.left, rect.top);
    m_body_def.type = b2_dynamicBody;
    m_body = world.CreateBody(&m_body_def);
    m_polygon_shape.SetAsBox(rect.width, rect.height);
    m_fixture_def.shape = &m_polygon_shape;
    m_fixture_def.density = 1;
    m_fixture_def.friction = 1;
    m_fixture_def.restitution = 1;
    m_body->CreateFixture(&m_fixture_def);
}

b2Vec2 RectBody::get_position() {
    return m_body->GetPosition();
}

float RectBody::get_rotation() {
    return m_body->GetAngle();
}