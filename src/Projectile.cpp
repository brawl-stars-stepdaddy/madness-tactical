#include "Projectile.hpp"
#include "World.hpp"

void Projectile::draw_current(sf::RenderTarget &target, sf::RenderStates states)
const {
    target.draw(m_sprite, states);
}

void Projectile::update_current(sf::Time delta_time) {
    setPosition(
            {m_body.get_position().x * World::SCALE,
             m_body.get_position().y * World::SCALE}
    );
    setRotation(m_body.get_rotation() * 60);
}

CircleBody &Projectile::get_body() {
    return m_body;
}

EntityType Projectile::get_type() {
    return EntityType::BOX;
}

void Projectile::on_collision(Entity *other_object) {
    // TODO
}

void Projectile::on_explosion(const Explosion &) {
    // TODO
}
