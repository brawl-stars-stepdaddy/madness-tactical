#include "Laser.hpp"
#include <cmath>
#include "EventManager.hpp"
#include "ExplosionEntity.hpp"
#include "GuiUtil.hpp"
#include "Unit.hpp"
#include "World.hpp"

Laser::Laser(World &world, Unit *parent) : RotatableWeapon(world) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(m_world->get_texture_holder().get(TexturesID::LASER));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 4.f, bounds.height / 2.f);
    float width = 1, height = 0.6;
    GuiUtil::shrink_to_rect_scale(m_sprite, width * 2, height * 2);
}

void Laser::update_current(sf::Time delta_time) {
    RotatableWeapon::update_current(delta_time);
    m_sprite.setRotation(m_angle * 180 / M_PIf);
    if (m_is_active) {
        if (m_current_frequency % m_frequency == 0) {
            create_new_explosion();
        }
        m_current_frequency++;
        m_active_time -= delta_time.asSeconds();
    }
    if (m_active_time < 0) {
        m_is_active = false;
        m_is_rotation_blocked = false;
        m_active_time = m_default_active_time;
        m_explosions_number = 0;
    }
}

void Laser::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    RotatableWeapon::draw_current(target, states);
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void Laser::launch() {
    m_is_active = true;
    m_is_rotation_blocked = true;
    float angle = m_angle;
    if (Weapon::m_parent->get_direction() == -1) {
        angle = M_PI - angle;
    }
    angle += Weapon::m_parent->getRotation() / (180 / M_PI);
    m_start_position = {
        m_parent->get_body().get_position().x + cos(angle) * 1.5f,
        m_parent->get_body().get_position().y + sin(angle) * 1.5f};
    m_direction = {
        cos(angle) * m_ray_radius * 1.2f, sin(angle) * m_ray_radius * 1.2f};
}

void Laser::create_new_explosion() {
    sf::Vector2f position = m_start_position;
    position.x += m_direction.x * m_explosions_number;
    position.y += m_direction.y * m_explosions_number;
    m_world->add_entity(std::make_unique<ExplosionEntity>(
        *m_world, Explosion({position.x, position.y}, m_ray_radius)
    ));
    m_explosions_number++;
}