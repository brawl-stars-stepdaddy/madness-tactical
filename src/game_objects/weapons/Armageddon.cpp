#include "game_objects/entities/Unit.hpp"
#include "game_objects/weapons/Armageddon.hpp"
#include "game_objects/weapons/ArmageddonProcess.hpp"
#include "logic/World.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"

Armageddon::Armageddon(World &world, Unit *parent) : Weapon(world) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(m_world->get_texture_holder().get(TexturesID::CASE));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 4.f, bounds.height / 2.f);
    float width = 1, height = 0.6;
    GuiUtil::shrink_to_rect_scale(m_sprite, width * 3, height * 3);
}

void Armageddon::update_current(sf::Time delta_time) {
}

void Armageddon::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void Armageddon::launch() {
    if (Weapon::m_parent->get_team()->get_available_number_weapons(WeaponType::ARMAGEDDON) > 0) {
        Weapon::launch();
        m_world->add_process(std::make_unique<ArmageddonProcess>(m_world));
    }
    Weapon::m_parent->get_team()->remove_weapon(WeaponType::ARMAGEDDON);
}

WeaponControllerType Armageddon::get_controller_type() {
    return DISTANT;
}
