#include "Bazooka.hpp"
#include "Unit.hpp"
#include <cmath>
#include "EventManager.hpp"
#include "ActionEventData.hpp"
#include "World.hpp"
#include "GuiUtil.hpp"
#include "CollisionProjectile.hpp"

Bazooka::Bazooka(World *world, Unit *parent) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(world->get_texture_holder().get(TexturesID::BAZOOKA));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 4.f, bounds.height / 2.f);
    float width = 1, height = 0.6;
    GuiUtil::shrink_to_rect_scale(m_sprite, width * 2, height * 2);
}

void Bazooka::update_current(sf::Time delta_time) {
    ChargeableWeapon::update_current(delta_time);
    m_sprite.setRotation(m_angle * 180 / M_PIf);
}

void Bazooka::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
    ChargeableWeapon::draw_current(target, states);
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void Bazooka::launch(World &world) {
    if (!m_is_charging) {
        return;
    }
    m_is_charging = false;
    float impulse_value = m_charge_level * 20;
    m_charge_level = m_init_charge_level;
    sf::Vector2f start_position = {
            m_parent->get_body().get_position().x +
            cos(m_angle) * m_parent->get_direction() * 2,
            m_parent->get_body().get_position().y + sin(m_angle) * 2};
    sf::Vector2f impulse = {
            cos(m_angle) * m_parent->get_direction() * impulse_value,
            sin(m_angle) * impulse_value};
    world.get_layer(World::Layer::ENTITIES)->attach_child(std::make_unique<CollisionProjectile>(
            &world, start_position, impulse, m_projectile_radius, m_explosion_radius
    ));
}
