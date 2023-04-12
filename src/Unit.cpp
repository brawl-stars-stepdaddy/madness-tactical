#include "Unit.hpp"
#include <iostream>
#include "EventManager.hpp"
#include "ExplosionEventData.hpp"
#include "ResourceHolder.hpp"
#include "World.hpp"
#include "GuiUtil.hpp"

TexturesID to_texture_id(Unit::Type type) {
    switch (type) {
        case Unit::Type::ENGINEER:
            return TexturesID::ENGINEER;
        case Unit::Type::WORM:
            return TexturesID::WORM;
        default:
            throw std::runtime_error("to_texture_id - failed to map Unit::Type"
            );
    }
}

Unit::Unit(Unit::Type type, World *world, sf::Vector2f center, float radius)
    : m_type(type),
      m_sprite(world->get_texture_holder().get(to_texture_id(type))),
      m_body(UnitBody(this, world->get_physics_world(), center, radius)),
      m_jump_sensor(JumpSensor(this, world, {center.x, center.y + radius}, radius / 2)) {
    GuiUtil::shrink_to_rect_scale(m_sprite, radius * 2, radius * 2);
    GuiUtil::center(m_sprite);

    b2WeldJointDef joint_def;
    joint_def.bodyA = m_body.get_b2Body();
    joint_def.bodyB = m_jump_sensor.get_body().get_b2Body();
    joint_def.localAnchorA = {0, radius};
    joint_def.localAnchorB = {0, 0};
    joint_def.collideConnected = false;
    world->get_physics_world().CreateJoint(&joint_def);
}


void Unit::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void Unit::update_current(sf::Time delta_time) {
    move(delta_time, m_direction);
    setPosition(
        {m_body.get_position().x * World::SCALE,
         m_body.get_position().y * World::SCALE}
    );
    setRotation(m_body.get_rotation() * 60);
    reset();
}

UnitBody &Unit::get_body() {
    return m_body;
}

EntityType Unit::get_type() {
    return EntityType::UNIT;
}

void Unit::on_collision(Entity *) {
}

void Unit::on_explosion(const Explosion &) {
}

float Unit::get_direction() const {
    return m_direction;
}

void Unit::set_weapon(Weapon *weapon) {
    m_weapon = weapon;
}

Weapon *Unit::get_weapon() const {
    return m_weapon;
}

void Unit::set_direction(float direction) {
    if (direction != m_direction) {
        m_direction = direction;
        scale(-1, 1);
    }
}

void Unit::move(sf::Time delta_time, float direction) {
    if (m_is_moving) {
        auto vertical_velocity = m_body.get_b2Body()->GetLinearVelocity().y;
        m_body.get_b2Body()->SetLinearVelocity({100 * direction * delta_time.asSeconds(), vertical_velocity});
    }
}

void Unit::jump_forward() {
    if (m_jump_ability) {
        m_body.get_b2Body()->SetLinearVelocity({m_direction * 2, -5});
    }
}

void Unit::jump_backward() {
    if (m_jump_ability) {
        m_body.get_b2Body()->SetLinearVelocity({-m_direction * 2, -5});
    }
}

void Unit::set_jump_ability(bool new_value) {
    m_jump_ability = new_value;
}

void Unit::set_is_moving(bool is_moving) {
    m_is_moving = is_moving;
}

void Unit::reset() {
    m_is_moving = false;
}
