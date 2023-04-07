#include "UnitBody.hpp"

UnitBody::UnitBody(b2World &world, std::pair<float, float> &position) {
    b2BodyDef unit_def;
    unit_def.position.Set(position.first, position.second);
    unit_def.fixedRotation = true;
    unit_def.type = b2BodyType::b2_dynamicBody;
    m_body = world.CreateBody(&unit_def);

    b2PolygonShape unit_body_shape, unit_sensor_shape;
    unit_body_shape.SetAsBox(1.0f, 2.0f);
    unit_sensor_shape.SetAsBox(0.1f, 0.1f, {-2.0f, 0}, 0.0f);

    b2FixtureDef unit_body_fixture, unit_sensor_fixture;
    unit_body_fixture.shape = &unit_body_shape;
    unit_body_fixture.friction = 1.0f;
    unit_body_fixture.restitution = 0.5f;
    unit_sensor_fixture.isSensor = true;

    m_body->CreateFixture(&unit_body_fixture);
    m_body->CreateFixture(&unit_sensor_fixture);
}

sf::Vector2f UnitBody::get_position() {
    return {m_body->GetPosition().x, m_body->GetPosition().y};
}

float UnitBody::get_rotation() {
    return 0;
}
