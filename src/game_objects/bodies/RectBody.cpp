#include "game_objects/bodies/RectBody.hpp"

RectBody::RectBody() = default;

RectBody::RectBody(Entity *parent, b2World &world, sf::FloatRect rect) {
    b2BodyDef m_body_def;
    b2PolygonShape m_polygon_shape;
    b2FixtureDef m_fixture_def;

    m_body_def.position.Set(rect.left, rect.top);
    m_body_def.type = b2_dynamicBody;
    m_body_def.userData.pointer = reinterpret_cast<uintptr_t>(parent);

    m_body = world.CreateBody(&m_body_def);
    m_polygon_shape.SetAsBox(rect.width, rect.height);
    m_fixture_def.shape = &m_polygon_shape;
    m_fixture_def.density = 1e9;
    m_fixture_def.friction = 1.0f;
    m_fixture_def.restitution = 0.0f;
    m_body->CreateFixture(&m_fixture_def);
}

sf::Vector2f RectBody::get_position() const {
    b2Vec2 pos = m_body->GetPosition();
    return {pos.x, pos.y};
}

float RectBody::get_rotation() const {
    return m_body->GetAngle();
}