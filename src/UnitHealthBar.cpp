#include "UnitHealthBar.hpp"
#include <string>
#include "GuiUtil.hpp"
#include "Unit.hpp"
#include "World.hpp"

UnitHealthBar::UnitHealthBar(World &world, Unit *parent, const sf::Font &font)
    : SceneNode(world), m_parent(parent) {
    m_text.setFont(font);
    m_text.setCharacterSize(150);
    m_text.setOutlineThickness(5);
    m_text.setOutlineColor(sf::Color(0, 0, 0));
    if (parent->get_team()) {
        m_text.setFillColor(parent->get_team()->get_team_color());
    }
    m_text.setString(std::to_string(m_parent->get_health()));

    sf::FloatRect bounds = get_text().getLocalBounds();
    setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setPosition(30, -150);
    setScale({0.4, 0.4});
}

void UnitHealthBar::draw_current(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.draw(m_text, states);
}

sf::Text UnitHealthBar::get_text() {
    return m_text;
}

void UnitHealthBar::update_current(sf::Time delta_time) {
    if (m_parent->get_team()) {
        m_text.setFillColor(m_parent->get_team()->get_team_color());
    }
    if (m_parent->get_direction() != m_direction) {
        m_direction *= -1;
        scale(-1, 1);
    }
    m_text.setString(std::to_string(m_parent->get_health()));
}
