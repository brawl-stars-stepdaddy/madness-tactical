#include <cmath>
#include "game_objects/weapons/Bazooka.hpp"
#include "game_objects/entities/CollisionProjectile.hpp"
#include "game_objects/entities/Unit.hpp"
#include "logic/World.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"

Bazooka::Bazooka(World &world, Unit *parent) : ChargeableWeapon(world) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(m_world->get_texture_holder().get(TexturesID::BAZOOKA));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 4.f, bounds.height / 2.f);
    float width = 1, height = 0.6;
    GuiUtil::shrink_to_rect_scale(m_sprite, width * 3, height * 3);
}

void Bazooka::update_current(sf::Time delta_time) {
    ChargeableWeapon::update_current(delta_time);
    m_sprite.setRotation(m_angle * 180 / M_PIf);
}

void Bazooka::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    ChargeableWeapon::draw_current(target, states);
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void Bazooka::launch() {
    if (Weapon::m_parent->get_team()->get_available_number_weapons(WeaponType::ARMAGEDDON) == 0) {
        return;
    }
    Weapon::m_parent->get_team()->remove_weapon(WeaponType::BAZOOKA);
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
    angle += static_cast<float>(Weapon::m_parent->getRotation() / (180 / M_PI));
    m_charge_level = m_init_charge_level;
    sf::Vector2f start_position = {
        m_parent->get_body().get_position().x + cos(angle) * 3,
        m_parent->get_body().get_position().y + sin(angle) * 3};
    sf::Vector2f impulse = {
        cos(angle) * impulse_value, sin(angle) * impulse_value};
    m_world->get_layer(World::Layer::ENTITIES)
        ->attach_child(std::make_unique<CollisionProjectile>(
            *m_world, start_position, impulse, m_projectile_radius,
            m_explosion_radius, true, false, TexturesID::CANON_BALL
        ));
}
