#include "Unit.hpp"
#include <iostream>
#include "EventManager.hpp"
#include "ExplosionEventData.hpp"
#include "ResourceHolder.hpp"

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
      m_jump_sensor(JumpSensor(this, world, {center.x, center.y + radius}, radius / 4)) {
    m_sprite.setScale(
        radius * World::SCALE * 2 / m_sprite.getLocalBounds().width,
        radius * World::SCALE * 2 / m_sprite.getLocalBounds().height
    );
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

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
    setPosition(
        {m_body.get_position().x * World::SCALE,
         m_body.get_position().y * World::SCALE}
    );
    setRotation(m_body.get_rotation() * 60);
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

void Unit::move(sf::Time delta_time, float direction) {
    if (direction != m_direction) {
        m_direction = direction;
        scale(-1, 1);
    }
    auto vertical_velocity = m_body.get_b2Body()->GetLinearVelocity().y;
    m_body.get_b2Body()->SetLinearVelocity({100 * direction * delta_time.asSeconds(), vertical_velocity});
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
