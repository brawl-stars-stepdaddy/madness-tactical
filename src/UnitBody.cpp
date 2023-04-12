#include "UnitBody.hpp"

UnitBody::UnitBody(
    Unit *parent,
    b2World &world,
    sf::Vector2f center,
    float radius
) {
    b2BodyDef unit_def;
    unit_def.position.Set(center.x, center.y);
    unit_def.fixedRotation = true;
    unit_def.type = b2BodyType::b2_dynamicBody;
    unit_def.userData.pointer = reinterpret_cast<uintptr_t>(parent);
    m_body = world.CreateBody(&unit_def);

    b2CircleShape unit_body_shape;
    b2PolygonShape unit_sensor_shape;
    unit_body_shape.m_radius = radius;
    unit_sensor_shape.SetAsBox(0.1f, 0.1f, {-2.0f, 0}, 0.0f);

    b2FixtureDef unit_body_fixture, unit_sensor_fixture;
    unit_body_fixture.shape = &unit_body_shape;
    unit_body_fixture.density = 1.0f;
    unit_body_fixture.friction = 1.0f;
    unit_body_fixture.restitution = 0.5f;
    unit_sensor_fixture.isSensor = true;
    unit_sensor_fixture.shape = &unit_sensor_shape;

    m_body->CreateFixture(&unit_body_fixture);
    m_body->CreateFixture(&unit_sensor_fixture);
}

sf::Vector2f UnitBody::get_position() {
    b2Vec2 pos = m_body->GetPosition();
    return {pos.x, pos.y};
}

float UnitBody::get_rotation() {
    return m_body->GetAngle();
}
