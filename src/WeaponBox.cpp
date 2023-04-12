#include "WeaponBox.hpp"


WeaponBox::WeaponBox(World &world, sf::FloatRect rect) {
    m_sprite = static_cast<sf::Sprite>(world.get_texture_holder().get(TexturesID::WEAPON_BOX));
    m_body = RectBody(this, world.get_physics_world(), rect);
    m_body.get_b2Body()->SetFixedRotation(true);
    m_sprite.setScale(
            rect.width * World::SCALE * 3 / m_sprite.getLocalBounds().width,
            rect.height * World::SCALE * 3 / m_sprite.getLocalBounds().height
    );
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
