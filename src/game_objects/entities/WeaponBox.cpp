#include "game_objects/entities/WeaponBox.hpp"
#include "game_objects/entities/Unit.hpp"
#include "logic/World.hpp"
#include "logic/events/event_data/DestructionEventData.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"

WeaponBox::WeaponBox(World &world, sf::FloatRect rect) : Box(world) {
    m_sprite = static_cast<sf::Sprite>(
        m_world->get_texture_holder().get(TexturesID::WEAPON_BOX)
    );
    m_body = RectBody(this, m_world->get_physics_world(), rect);
    m_body.get_b2Body()->SetFixedRotation(true);
    GuiUtil::shrink_to_rect_scale(m_sprite, rect.width * 3, rect.height * 3);
    GuiUtil::center(m_sprite);
}

void WeaponBox::on_collision(std::shared_ptr<Entity> other_object) {
    if (other_object->get_type() == EntityType::UNIT) {
        auto unit = std::static_pointer_cast<Unit>(other_object);
        Team *team = unit->get_team();
        if (team) {
            auto type = static_cast<WeaponType>(random() % WEAPON_TYPES_NUMBER);
            team->add_weapon(type);
        }
        m_body.get_b2Body()->SetEnabled(false);
        m_world->get_event_manager()->queue_event(
            std::make_unique<DestructionEventData>(this)
        );
    }
}
