#include "Projectile.hpp"
#include "DestructionEventData.hpp"
#include "ExplosionEntity.hpp"
#include "World.hpp"

Projectile::Projectile(
    World &world,
    sf::Vector2f center,
    sf::Vector2f impulse,
    float radius,
    float explosion_radius,
    bool is_sensor,
    bool is_static,
    TexturesID texture
)
    : Entity(world),
      m_sprite(m_world->get_texture_holder().get(texture)),
      m_body(CircleBody(
          this,
          m_world->get_physics_world(),
          center,
          radius,
          is_sensor,
          is_static
      )),
      m_explosion_radius(explosion_radius) {
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setScale(
        radius * World::SCALE * 2 / bounds.width,
        radius * World::SCALE * 2 / bounds.height
    );
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    m_body.get_b2Body()->ApplyLinearImpulseToCenter(
        {impulse.x, impulse.y}, true
    );
}

void Projectile::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void Projectile::update_current(sf::Time delta_time) {
    Entity::update_current(delta_time);
}

CircleBody &Projectile::get_body() {
    return m_body;
}

EntityType Projectile::get_type() {
    return EntityType::PROJECTILE;
}

void Projectile::on_collision(std::shared_ptr<Entity> other_object) {
}

void Projectile::on_explosion(const Explosion &) {
}
