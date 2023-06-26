#include "Label.hpp"
#include "ResourceHolder.hpp"
#include "GuiUtil.hpp"

namespace GUI {
Label::Label(const std::string &text, const FontHolder &fonts)
    : m_text(text, fonts.get(FontsID::SANSATION), 32) {
    GuiUtil::center(m_text);
}

bool Label::is_selectable() {
    return false;
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_text, states);
}

void Label::set_text(const std::string &text) {
    m_text.setString(text);
}

    void Label::handle_input(const sf::Event &event) {

    }
}  // namespace GUI