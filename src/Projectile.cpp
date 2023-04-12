#include "Projectile.hpp"

Projectile::Projectile(World &world, sf::Vector2f center, sf::Vector2f impulse, float radius, float explosion_radius)
        : m_sprite(world.get_texture_holder().get(TexturesID::CANON_BALL)),
          m_body(CircleBody(this, world.get_physics_world(), center, radius, true)),
          explosion_radius(explosion_radius) {
    m_sprite.setScale(
            radius * World::SCALE * 2 / m_sprite.getLocalBounds().width,
            radius * World::SCALE * 2 / m_sprite.getLocalBounds().height
    );
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    m_body.get_b2Body()->ApplyLinearImpulseToCenter({impulse.x, impulse.y}, true);
}

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
    if (!is_exploded) {
        is_exploded = true;
        auto world = m_body.get_b2Body()->GetWorld();
        auto center = m_body.get_position();
        world->DestroyBody(m_body.get_b2Body());
        m_body = CircleBody(this, *world, center, explosion_radius, true);
        return;
    }
    EventManager::get()->queue_event(std::make_unique<ExplosionEventData>(
            Explosion({m_body.get_position().x, m_body.get_position().y}, explosion_radius)));
    m_body.get_b2Body()->SetEnabled(false);

}

void Projectile::on_explosion(const Explosion &) {
    // TODO
}
