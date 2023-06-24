#include "Kettlebell.hpp"
#include "KettlebellProjectile.hpp"
#include "EventManager.hpp"
#include "GuiUtil.hpp"
#include "Unit.hpp"
#include "World.hpp"

Kettlebell::Kettlebell(World &world, Unit *parent) : Weapon(world) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(m_world->get_texture_holder().get(TexturesID::CASE));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 4.f, bounds.height / 2.f);
    float width = 1, height = 1;
    GuiUtil::shrink_to_rect_scale(m_sprite, width * 2, height * 2);
}

void Kettlebell::update_current(sf::Time delta_time) {}

void Kettlebell::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void Kettlebell::launch() {
    sf::Vector2f position = Weapon::m_parent->get_camera_position();
    b2Vec2 position_ = {position.x, position.y};
    position_.Normalize();
    position_ *= 80;
    position = {position_.x, position_.y};

    m_world->get_layer(World::Layer::ENTITIES)
            ->attach_child(std::make_unique<KettlebellProjectile>(
                    *m_world, position, m_projectile_radius,
                    m_explosion_radius, TexturesID::KETTLEBELL
    ));
}

