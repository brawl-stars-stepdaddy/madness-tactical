#ifndef LABEL_HPP_
#define LABEL_HPP_

#include "Component.hpp"
#include "utils/ResourceIdentifiers.hpp"

namespace GUI {

struct Label : Component {
public:
    Label(const std::string &text, const FontHolder &fonts);

    virtual bool is_selectable() override;

    void set_text(const std::string &text);

    virtual void handle_input(const sf::Event &event) override;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
        const override;

    sf::Text m_text;
};
}  // namespace GUI

#endif
