#include <cmath>
#include "game_objects/entities/Unit.hpp"
#include "game_objects/UnitHealthBar.hpp"
#include "logic/World.hpp"
#include "logic/events/event_data/ExplosionEventData.hpp"
#include "logic/states/GameState.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"

Unit::Unit(
    World &world,
    sf::Vector2f center,
    float radius
)
    : Entity(world),
      m_sprite(m_world->get_texture_holder().get(TexturesID::UNIT)),
      m_body(UnitBody(this, m_world->get_physics_world(), center, radius)) {
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

void Unit::on_collision(std::shared_ptr<Entity> other_object) {
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
    float distance = sqrtf(powf(x_vector, 2) + powf(y_vector, 2));
    float x_impulse = 100 * x_vector / powf(distance, 2);
    float y_impulse = 100 * y_vector / powf(distance, 2);
    physic_body->ApplyLinearImpulseToCenter({x_impulse, y_impulse}, true);

    change_health(static_cast<int>(std::max(
        static_cast<float>(-m_health),
        -sqrtf(powf(x_impulse, 2) + powf(y_impulse, 2))
    )));
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
                b2Min(abs(horizontal_projection + 10.0f * direction), 10.0f) -
            horizontal_projection;
        float impulse = m_body.get_b2Body()->GetMass() * horizontal_change;
        float angle = atan2f(normal.x, normal.y);

        m_body.get_b2Body()->ApplyLinearImpulseToCenter(
            {impulse * sin(angle), impulse * cos(angle)}, true
        );
    }
}

void Unit::stop_move(sf::Time delta_time) {
    if (!m_moving_active && m_dumping_active) {
        auto current_velocity = m_body.get_b2Body()->GetLinearVelocity();
        float horizontal_change = -current_velocity.x * 0.9f;
        float vertical_change = -current_velocity.y * 0.9f;
        b2Vec2 impulse = {
            m_body.get_b2Body()->GetMass() * horizontal_change,
            m_body.get_b2Body()->GetMass() * vertical_change,
        };
        m_body.get_b2Body()->ApplyLinearImpulseToCenter(impulse, true);
    }
}

void Unit::big_jump() {
    if (m_jumping_active) {
        b2Vec2 vertical = m_body.get_b2Body()->GetPosition();
        b2Vec2 horizontal = {-vertical.y, vertical.x};
        vertical.Normalize();
        horizontal.Normalize();
        horizontal *= m_direction * 60;
        vertical *= 150;
        m_body.get_b2Body()->ApplyLinearImpulseToCenter(
            horizontal + vertical, true
        );
    }
}

void Unit::small_jump() {
    if (m_jumping_active) {
        b2Vec2 vertical = m_body.get_b2Body()->GetPosition();
        b2Vec2 horizontal = {-vertical.y, vertical.x};
        vertical.Normalize();
        horizontal.Normalize();
        horizontal *= m_direction * 80;
        vertical *= 50;
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
    if (m_is_active && value < 0) {
        auto game_state = dynamic_cast<GameState *>(m_world->get_game_state());
        game_state->get_logic_state_stack()->clear_states();
        game_state->get_logic_state_stack()->push_state(StatesID::BLOODY_FATALITY
        );
    }
    m_health += value;
    if (m_team) {
        m_team->change_health(value);
    }
    if (m_health <= 0) {
        m_world->add_bloody_fatality_candidate(this);
    }
}

void Unit::kill_unit() {
    if (m_team) {
        m_team->remove_unit(this);
    }
    m_body.get_b2Body()->GetWorld()->DestroyBody(m_body.get_b2Body());
    detach();
}

sf::Vector2f Unit::get_camera_position() const {
    return m_world->get_camera_position();
}

const sf::Sprite &Unit::get_sprite() const {
    return m_sprite;
}

bool Unit::get_jumping_active() const {
    return m_jumping_active;
}
