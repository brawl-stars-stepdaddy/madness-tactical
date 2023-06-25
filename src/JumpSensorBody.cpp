#include "JumpSensorBody.hpp"

JumpSensorBody::JumpSensorBody(
    JumpSensor *parent,
    b2World &world,
    sf::Vector2f center,
    float radius
) {
    b2BodyDef sensor_def;
    sensor_def.position.Set(center.x, center.y);
    sensor_def.type = b2BodyType::b2_dynamicBody;
    sensor_def.userData.pointer = reinterpret_cast<uintptr_t>(parent);
    m_body = world.CreateBody(&sensor_def);

    b2CircleShape unit_sensor_shape;
    unit_sensor_shape.m_radius = radius / 4;
    unit_sensor_shape.m_p = {0, radius};

    b2FixtureDef unit_sensor_fixture;
    unit_sensor_fixture.isSensor = true;
    unit_sensor_fixture.shape = &unit_sensor_shape;

    m_body->CreateFixture(&unit_sensor_fixture);

    unit_sensor_shape.m_radius = radius / 10;
    unit_sensor_fixture.shape = &unit_sensor_shape;
    unit_sensor_fixture.density = 1.0f;

    m_body->CreateFixture(&unit_sensor_fixture);
}

sf::Vector2f JumpSensorBody::get_position() const {
    b2Vec2 pos = m_body->GetPosition();
    return {pos.x, pos.y};
}

float JumpSensorBody::get_rotation() const {
    return m_body->GetAngle();
}
