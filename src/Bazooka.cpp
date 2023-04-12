#include "Bazooka.hpp"
#include "Unit.hpp"
#include <cmath>
#include "World.hpp"
#include "GuiUtil.hpp"

Bazooka::Bazooka(World *world, Unit *parent) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(world->get_texture_holder().get(TexturesID::BAZOOKA));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 4.f, bounds.height / 2.f);
    float width = 1, height = 0.6;
    GuiUtil::shrink_to_rect_scale(m_sprite, width * 2, height * 2);
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
    if (m_is_charging) {
        int charge_steps = 20;
        int steps = static_cast<int>(m_charge_level * charge_steps);
        sf::Vector2f direction = {
                cos(m_angle) * m_parent->get_direction(),
                sin(m_angle)
        };
        for (int i = 0; i < steps; i++) {
            sf::Vector2f pos = m_parent->get_body().get_position() + direction * (1.f + 2.f * i / charge_steps);
            sf::CircleShape circle;
            circle.setPosition(pos * World::SCALE);
            circle.setRadius((0.25f + 0.25f / charge_steps * i) * World::SCALE);
            circle.setFillColor(sf::Color(255, 255.f / charge_steps * i, 0));
            target.draw(circle);
        }
    }
}

void Bazooka::charge(sf::Time delta_time) {
    m_charge_level = std::min(1.0f, m_charge_level + delta_time.asSeconds() * 0.5f);
}

void Bazooka::change_angle(sf::Time delta_time, float direction) {
    m_angle = std::min(M_PI_2f, std::max(-M_PI_2f, m_angle + delta_time.asSeconds() * 0.5f * -direction));
}

std::unique_ptr<Projectile> Bazooka::launch(World &world) {
    float impulse_value = m_charge_level * 5;
    m_charge_level = 0.1f;
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
