#include "game_objects/entities/Unit.hpp"
#include "game_objects/weapons/ChargeableWeapon.hpp"
#include "logic/World.hpp"
#include "logic/events/event_data/ActionEventData.hpp"
#include "utils/ResourceHolder.hpp"

void ChargeableWeapon::update_current(sf::Time delta_time) {
    RotatableWeapon::update_current(delta_time);
    if (m_is_charging) {
        charge(delta_time);
    }
}

void ChargeableWeapon::draw_current(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    RotatableWeapon::draw_current(target, states);
    if (!m_is_hidden && m_is_charging) {
        int charge_steps = 20;
        int steps = static_cast<int>(m_charge_level * (static_cast<float>(charge_steps) - 0.1f));
        float angle = m_angle;
        if (Weapon::m_parent->get_direction() == -1) {
            angle = M_PI - angle;
        }
        angle += Weapon::m_parent->getRotation() / (180 / M_PIf);
        sf::Vector2f direction = {cos(angle), sin(angle)};
        for (int i = 0; i < steps; i++) {
            sf::Vector2f pos = m_parent->get_body().get_position() +
                               direction * (2.f + 2.f * static_cast<float>(i) / static_cast<float>(charge_steps));
            sf::CircleShape circle;
            circle.setRadius((0.25f + 0.25f / static_cast<float>(charge_steps) * static_cast<float>(i)) * World::SCALE);
            circle.setFillColor(sf::Color(255, static_cast<int>(255.f / static_cast<float>(charge_steps)) * i, 0));
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setPosition(pos * World::SCALE);
            target.draw(circle);
        }
    }
}

void ChargeableWeapon::set_currently_charging(bool is_charging) {
    m_is_charging = is_charging;
}

void ChargeableWeapon::charge(sf::Time delta_time) {
    m_charge_level = std::min(1.0f, m_charge_level + delta_time.asSeconds() * 0.5f);
    if (m_charge_level >= 1.0f) {
        m_world->get_event_manager()->queue_event(
            std::make_unique<LaunchProjectileEventData>()
        );
    }
}

ChargeableWeapon::ChargeableWeapon(World &world) : RotatableWeapon(world) {}
