#include "WeaponBox.hpp"
#include "GuiUtil.hpp"

WeaponBox::WeaponBox(World &world, sf::FloatRect rect) {
    m_sprite = static_cast<sf::Sprite>(world.get_texture_holder().get(TexturesID::WEAPON_BOX));
    m_body = RectBody(this, world.get_physics_world(), rect);
    m_body.get_b2Body()->SetFixedRotation(true);
    GuiUtil::shrink_to_rect_scale(m_sprite, rect.width * 3, rect.height * 3);
    GuiUtil::center(m_sprite);
}
