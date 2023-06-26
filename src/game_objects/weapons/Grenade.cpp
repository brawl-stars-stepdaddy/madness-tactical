#include "game_objects/weapons/Grenade.hpp"
#include <cmath>
#include "game_objects/entities/TimerProjectile.hpp"
#include "game_objects/entities/Unit.hpp"
#include "logic/World.hpp"
#include "logic/events/EventManager.hpp"
#include "utils/GuiUtil.hpp"

Grenade::Grenade(World &world, Unit *parent) : ChargeableWeapon(world) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(m_world->get_texture_holder().get(TexturesID::GRENADE));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setScale(
        m_projectile_radius * World::SCALE * 2 / bounds.width,
        m_projectile_radius * World::SCALE * 2 / bounds.height
    );
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Grenade::update_current(sf::Time delta_time) {
    ChargeableWeapon::update_current(delta_time);
    m_sprite.setRotation(m_angle * 180 / M_PIf);
}

void Grenade::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    ChargeableWeapon::draw_current(target, states);
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void Grenade::launch() {
    Weapon::launch();
    if (!m_is_charging) {
        return;
    }
    set_currently_charging(false);
    float impulse_value = m_charge_level * 20;
    float angle = m_angle;
    if (Weapon::m_parent->get_direction() == -1) {
        angle = M_PI - angle;
    }
    angle += Weapon::m_parent->getRotation() / (180 / M_PI);
    m_charge_level = m_init_charge_level;
    sf::Vector2f start_position = {
        m_parent->get_body().get_position().x + cos(angle) * 2,
        m_parent->get_body().get_position().y + sin(angle) * 2};
    sf::Vector2f impulse = {
        cos(angle) * impulse_value, sin(angle) * impulse_value};
    m_world->get_layer(World::Layer::ENTITIES)
        ->attach_child(std::make_unique<TimerProjectile>(
            *m_world, start_position, impulse, m_projectile_radius,
            m_explosion_radius, 0, m_explosion_time, false, false,
            TexturesID::GRENADE
        ));
}
