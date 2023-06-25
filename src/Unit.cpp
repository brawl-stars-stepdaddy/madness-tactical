#include "Unit.hpp"
#include <DestructionEventData.hpp>
#include <World.hpp>
#include <cmath>
#include <iostream>
#include "EventManager.hpp"
#include "ExplosionEventData.hpp"
#include "GuiUtil.hpp"
#include "ResourceHolder.hpp"
#include "UnitHealthBar.hpp"
#include "Weapon.hpp"

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

Unit::Unit(
    World &world,
    Unit::Type type,
    sf::Vector2f center,
    float radius,
    int player_id
)
    : Entity(world),
      m_type(type),
      m_sprite(m_world->get_texture_holder().get(to_texture_id(type))),
      m_body(UnitBody(this, m_world->get_physics_world(), center, radius)),
      m_player_id(player_id) {
    GuiUtil::shrink_to_rect_scale(m_sprite, radius * 2, radius * 2);
    GuiUtil::center(m_sprite);

    auto health_bar = std::make_unique<UnitHealthBar>(
        *m_world, this, m_world->get_font_holder().get(FontsID::BAGEL_FONT)
    );
    this->attach_child(std::move(health_bar));
}

void Unit::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    target.draw(m_sprite, states);
}

void Unit::update_current(sf::Time delta_time) {
    Entity::update_current(delta_time);
    if (m_body.get_b2Body()->GetLinearVelocity().LengthSquared() < 1e-1) {
        m_jumping_active = true;
        m_dumping_active = false;
    } else {
        m_jumping_active = false;
    }
    move(delta_time, m_direction);
    stop_move(delta_time);
    reset();
}

UnitBody &Unit::get_body() {
    return m_body;
}

EntityType Unit::get_type() {
    return EntityType::UNIT;
}

void Unit::on_collision(Entity *other_object) {
    if (other_object->get_type() == EntityType::MAP) {
        m_dumping_active = true;
    }
}

void Unit::on_explosion(const Explosion &explosion) {
    auto [x, y] = m_body.get_position();
    auto [x_explosion, y_explosion] = explosion.get_coordinates();
    auto physic_body = m_body.get_b2Body();
    float x_vector = x - x_explosion;
    float y_vector = y - y_explosion;
    float distance = sqrt(pow(x_vector, 2) + pow(y_vector, 2));
    float x_impulse = 100 * x_vector / pow(distance, 2);
    float y_impulse = 100 * y_vector / pow(distance, 2);
    physic_body->ApplyLinearImpulseToCenter({x_impulse, y_impulse}, true);

    m_health -= sqrt(pow(x_impulse, 2) + pow(y_impulse, 2));
    if (m_health <= 0) {
        kill_unit();
    }
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
    if (m_jumping_active && m_moving_active) {
        b2Vec2 position = m_body.get_b2Body()->GetPosition();
        b2Vec2 normal = {-position.y, position.x};
        b2Vec2 current_velocity = m_body.get_b2Body()->GetLinearVelocity();
        float horizontal_projection =
            (b2Dot(current_velocity, normal) / b2Dot(normal, normal) * normal)
                .Length();
        float horizontal_change =
            direction *
                b2Min(abs(horizontal_projection + 5.0f * direction), 5.0f) -
            horizontal_projection;
        float impulse = m_body.get_b2Body()->GetMass() * horizontal_change;
        float angle = atan2(normal.x, normal.y);

        m_body.get_b2Body()->ApplyLinearImpulseToCenter(
            {impulse * sin(angle), impulse * cos(angle)}, true
        );
    }
}

void Unit::stop_move(sf::Time delta_time) {
    if (!m_moving_active && m_dumping_active) {
        auto current_velocity = m_body.get_b2Body()->GetLinearVelocity();
        float horizontal_change = -current_velocity.x * 0.9;
        float vertical_change = -current_velocity.y * 0.9;
        b2Vec2 impulse = {
            m_body.get_b2Body()->GetMass() * horizontal_change,
            m_body.get_b2Body()->GetMass() * vertical_change,
        };
        m_body.get_b2Body()->ApplyLinearImpulseToCenter(impulse, true);
    }
}

void Unit::jump_forward() {
    if (m_jumping_active) {
        b2Vec2 vertical = m_body.get_b2Body()->GetPosition();
        b2Vec2 horizontal = {-vertical.y, vertical.x};
        vertical.Normalize();
        horizontal.Normalize();
        horizontal *= m_direction * 30;
        vertical *= 30;
        m_body.get_b2Body()->ApplyLinearImpulseToCenter(
            horizontal + vertical, true
        );
    }
}

void Unit::jump_backward() {
    if (m_jumping_active) {
        b2Vec2 vertical = m_body.get_b2Body()->GetPosition();
        b2Vec2 horizontal = {-vertical.y, vertical.x};
        vertical.Normalize();
        horizontal.Normalize();
        horizontal *= -m_direction * 20;
        vertical *= 40;
        m_body.get_b2Body()->ApplyLinearImpulseToCenter(
            horizontal + vertical, true
        );
    }
}

void Unit::set_moving_active(bool new_value) {
    m_moving_active = new_value;
}

void Unit::set_dumping_active(bool new_value) {
    if (m_jumping_active) {
        m_dumping_active = new_value;
    }
}

void Unit::reset() {
    m_moving_active = false;
}

int Unit::get_health() const {
    return m_health;
}

void Unit::set_team(Team *team) {
    m_team = team;
}

Team *Unit::get_team() const {
    return m_team;
}

void Unit::set_activeness(bool new_value) {
    m_is_active = new_value;
    m_weapon->set_hidden(!new_value);
}

void Unit::change_health(int value) {
    m_health += value;
}

void Unit::kill_unit() {
    m_health = 0;
    if (m_team) {
        m_team->remove_unit(this);
    }
    m_body.get_b2Body()->SetEnabled(false);
    m_world->get_event_manager()->queue_event(
        std::make_unique<DestructionEventData>(this)
    );
}

sf::Vector2f Unit::get_camera_position() const {
    return m_world->get_camera_position();
}

const sf::Sprite &Unit::get_sprite() const {
    return m_sprite;
}
