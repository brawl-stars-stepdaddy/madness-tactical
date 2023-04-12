#include "Bazooka.hpp"
#include "Unit.hpp"
#include <cmath>
#include "EventManager.hpp"
#include "ActionEventData.hpp"
#include "World.hpp"

Bazooka::Bazooka(World *world, Unit *parent) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(world->get_texture_holder().get(TexturesID::BAZOOKA));
}

void Bazooka::reset() {
    Weapon::reset();
}

void Bazooka::update_current(sf::Time delta_time) {
    if (m_is_charging) {
        charge(delta_time);
    }
    change_angle(delta_time, m_current_angle_change_direction);
    m_sprite.setRotation(m_angle * 180 / M_PIf);
    reset();
}

void Bazooka::draw_current(sf::RenderTarget &target, sf::RenderStates states)
const {
    target.draw(m_sprite, states);
}

void Bazooka::charge(sf::Time delta_time) {
    m_charge_level = std::min(1.0f, m_charge_level + delta_time.asSeconds() * 0.5f);
    if (m_charge_level == 1.0f) {
        EventManager().get()->queue_event(std::make_unique<LaunchProjectileEventData>());
    }
}

void Bazooka::change_angle(sf::Time delta_time, float direction) {
    m_angle = std::min(M_PI_2f, std::max(-M_PI_2f, m_angle + delta_time.asSeconds() * 0.5f * -direction));
}

std::unique_ptr<Projectile> Bazooka::launch(World &world) {
    float impulse_value = m_charge_level * 10 ;
    m_charge_level = 0.2f;
    sf::Vector2f start_position = {
        m_parent->get_body().get_position().x +
            cos(m_angle) * m_parent->get_direction() * 2,
        m_parent->get_body().get_position().y + sin(m_angle) * 2};
    sf::Vector2f impulse = {
        cos(m_angle) * m_parent->get_direction() * impulse_value,
        sin(m_angle) * impulse_value};
    return std::make_unique<Projectile>(
        &world, start_position, impulse, m_projectile_radius, m_explosion_radius
    );
}
