#include "JumpSensor.hpp"
#include "World.hpp"
#include "CollisionEventData.hpp"

JumpSensor::JumpSensor(Unit *parent, World *world, sf::Vector2f center, float radius)
    : m_parent(parent),
      m_body(JumpSensorBody(this, world->get_physics_world(), center, radius)) {}

Body &JumpSensor::get_body() {
    return m_body;
}

void JumpSensor::on_collision(Entity *other_object) {
    if (other_object->get_type() == EntityType::MAP) {
        m_parent->set_jump_ability(true);
    }
}

void JumpSensor::end_collision(Entity *other_object) {
    if (other_object->get_type() == EntityType::MAP) {
        m_parent->set_jump_ability(false);
    }
}

EntityType JumpSensor::get_type() {
    return EntityType::JUMP_SENSOR;
}
