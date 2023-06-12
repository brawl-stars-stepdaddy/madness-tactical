#include "WeaponBox.hpp"
#include "GuiUtil.hpp"
#include "ResourceIdentifiers.hpp"
#include "World.hpp"

WeaponBox::WeaponBox(World &world, sf::FloatRect rect) : Box(world) {
    m_sprite = static_cast<sf::Sprite>(m_world->get_texture_holder().get(TexturesID::WEAPON_BOX));
    m_body = RectBody(this, m_world->get_physics_world(), rect);
    m_body.get_b2Body()->SetFixedRotation(true);
    GuiUtil::shrink_to_rect_scale(m_sprite, rect.width * 3, rect.height * 3);
    GuiUtil::center(m_sprite);
}
