#include "gui/Button.hpp"
#include "utils/GuiUtil.hpp"
#include "utils/ResourceHolder.hpp"

namespace GUI {
Button::Button(const FontHolder &fonts) {
    m_borders.setSize({160, 50});
    m_borders.setOrigin({80, 25});
    m_borders.setOutlineThickness(5);
    m_text.setFillColor(sf::Color(200, 200, 200));
    m_text.setFont(fonts.get(FontsID::SANSATION));
    m_borders.setOutlineColor(sf::Color(200, 200, 200));
    m_borders.setFillColor(sf::Color(0, 0, 0, 100));
}

void Button::set_callback(Button::Callback callback) {
    m_callback = std::move(callback);
}

void Button::set_text(const std::string &text) {
    m_text.setString(text);
    GuiUtil::center(m_text);
}

bool Button::is_selectable() {
    return true;
}

void Button::select() {
    Component::select();
    m_text.setFillColor(sf::Color(200, 200, 0));
    m_borders.setOutlineColor(sf::Color(200, 200, 0));
    m_borders.setFillColor(sf::Color(0, 0, 0, 200));
}

void Button::deselect() {
    Component::deselect();
    m_text.setFillColor(sf::Color(200, 200, 200));
    m_borders.setOutlineColor(sf::Color(200, 200, 200));
    m_borders.setFillColor(sf::Color(0, 0, 0, 100));
}

void Button::activate() {
    Component::activate();
    if (m_callback) {
        m_callback();
    }
    deactivate();
}

void Button::deactivate() {
    Component::deactivate();
}

void Button::handle_input(const sf::Event &event) {
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_borders, states);
    target.draw(m_text, states);
}
}  // namespace GUI
