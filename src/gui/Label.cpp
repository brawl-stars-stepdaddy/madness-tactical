#include "gui/Label.hpp"
#include "utils/ResourceHolder.hpp"

namespace GUI {
Label::Label(const std::string &text, const FontHolder &fonts)
    : m_text(text, fonts.get(FontsID::SANSATION), 16) {
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
}  // namespace GUI