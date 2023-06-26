#include "LandMine.hpp"
#include "EventManager.hpp"
#include "TimerProjectile.hpp"
#include "Unit.hpp"
#include "World.hpp"

LandMine::LandMine(World &world, Unit *parent) : Weapon(world) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(m_world->get_texture_holder().get(TexturesID::LAND_MINE)
    );
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setScale(
        m_projectile_radius * World::SCALE * 2 / bounds.width,
        m_projectile_radius * World::SCALE * 2 / bounds.height
    );
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void LandMine::update_current(sf::Time delta_time) {
}

void LandMine::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void LandMine::launch() {
    Weapon::launch();
    if (!Weapon::m_parent->get_jumping_active()) {
        return;
    }
    b2Vec2 position = {
        m_parent->get_body().get_position().x,
        m_parent->get_body().get_position().y};
    float distance = position.Normalize() - 1.0f;
    position *= distance;
    sf::Vector2f start_position = {position.x, position.y};
    sf::Vector2f impulse = {0, 0};
    m_world->get_layer(World::Layer::ENTITIES)
        ->attach_child(std::make_unique<TimerProjectile>(
            *m_world, start_position, impulse, m_projectile_radius,
            m_explosion_radius, m_activation_time, m_explosion_time, true, true,
            TexturesID::LAND_MINE
        ));
}

WeaponControllerType LandMine::get_controller_type() {
    return LAUNCH;
}
