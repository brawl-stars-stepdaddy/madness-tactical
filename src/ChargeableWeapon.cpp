#include "ChargeableWeapon.hpp"
#include "World.hpp"
#include "EventManager.hpp"
#include "ActionEventData.hpp"

void ChargeableWeapon::update_current(sf::Time delta_time) {
    RotatableWeapon::update_current(delta_time);
    if (m_is_charging) {
        charge(delta_time);
    }
}

void ChargeableWeapon::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_is_hidden && m_is_charging) {
        int charge_steps = 20;
        int steps = static_cast<int>(m_charge_level * (charge_steps - 0.1f));
        sf::Vector2f direction = {
                cos(m_angle) * m_parent->get_direction(),
                sin(m_angle)
        };
        for (int i = 0; i < steps; i++) {
            sf::Vector2f pos = m_parent->get_body().get_position() + direction * (2.f + 2.f * i / charge_steps);
            sf::CircleShape circle;
            circle.setRadius((0.25f + 0.25f / charge_steps * i) * World::SCALE);
            circle.setFillColor(sf::Color(255, 255.f / charge_steps * i, 0));
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
    if (m_charge_level == 1.0f) {
        EventManager().get()->queue_event(std::make_unique<LaunchProjectileEventData>());
    }
}
