#ifndef JUMP_SENSOR_BODY_HPP_
#define JUMP_SENSOR_BODY_HPP_

#include "Body.hpp"

struct JumpSensor;

struct JumpSensorBody : Body {
public:
    JumpSensorBody(JumpSensor *, b2World &world, sf::Vector2f center, float radius);
    sf::Vector2f get_position() override;
    float get_rotation() override;
};

#endif // JUMP_SENSOR_BODY_HPP_