#include "JumpSensor.hpp"
#include "CollisionEventData.hpp"
#include "World.hpp"

JumpSensor::JumpSensor(
    World &world,
    Unit *parent,
    sf::Vector2f center,
    float radius
)
    : Entity(world),
      m_parent(parent),
      m_body(JumpSensorBody(this, m_world->get_physics_world(), center, radius)
      ) {
}

Body &JumpSensor::get_body() {
    return m_body;
}

void JumpSensor::on_collision(Entity *other_object) {
    if (other_object->get_type() == EntityType::MAP) {
        // m_parent->set_jump_active(true);
    }
}

void JumpSensor::end_collision(Entity *other_object) {
    if (other_object->get_type() == EntityType::MAP) {
        // m_parent->set_jump_active(false);
    }
}

EntityType JumpSensor::get_type() {
    return EntityType::JUMP_SENSOR;
}
