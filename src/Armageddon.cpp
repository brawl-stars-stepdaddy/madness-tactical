#include "Armageddon.hpp"
#include "ArmageddonProcess.hpp"
#include "GuiUtil.hpp"
#include "World.hpp"

Armageddon::Armageddon(World &world, Unit *parent) : Weapon(world) {
    m_parent = parent;
    m_parent->set_weapon(this);
    m_sprite.setTexture(m_world->get_texture_holder().get(TexturesID::CASE));
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 4.f, bounds.height / 2.f);
    float width = 1, height = 1;
    GuiUtil::shrink_to_rect_scale(m_sprite, width * 2, height * 2);
}

void Armageddon::update_current(sf::Time delta_time) {}

void Armageddon::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_is_hidden) {
        target.draw(m_sprite, states);
    }
}

void Armageddon::launch() {
    m_world->add_process(std::make_unique<ArmageddonProcess>(m_world));
}

WeaponControllerType Armageddon::get_controller_type() {
    return DISTANT;
}
