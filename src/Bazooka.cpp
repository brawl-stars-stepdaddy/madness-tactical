#include "Bazooka.hpp"
#include <cmath>

Bazooka::Bazooka(Unit *parent) {
    m_parent = parent;
}

void Bazooka::charge(sf::Time delta_time) {
    m_charge_level += delta_time.asSeconds() * 2.0f;
}

void Bazooka::change_angle(sf::Time delta_time, bool direction) {
    if (direction) {
        m_angle = std::max(M_PI_2f, m_angle + delta_time.asSeconds() * 0.5f);
    }
    else {
        m_angle = std::min(-M_PI_2f, m_angle - delta_time.asSeconds() * 0.5f);
    }
}

std::unique_ptr<Projectile> Bazooka::launch(World &world) {
    float impulse_value = m_charge_level * 5;
    sf::Vector2f start_position = {m_parent->get_body().get_position().x + cos(m_angle) * m_parent->get_direction() * 2,
                                   m_parent->get_body().get_position().x + sin(m_angle) * 2};
    sf::Vector2f impulse = {cos(m_angle) * m_parent->get_direction() * impulse_value, sin(m_angle) * impulse_value};
    return std::make_unique<Projectile>(
            world, start_position, impulse, m_projectile_radius, m_explosion_radius);
}
