#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <functional>
#include "Component.hpp"
#include "utils/ResourceIdentifiers.hpp"

namespace GUI {

struct Button : Component {
public:
    typedef std::function<void()> Callback;

    explicit Button(const FontHolder &fonts);

    void set_callback(Callback callback);
    void set_text(const std::string &text);

    bool is_selectable() override;
    void select() override;
    void deselect() override;
    void activate() override;
    void deactivate() override;

    void handle_input(const sf::Event &event) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Callback m_callback;
    sf::Text m_text;
    sf::RectangleShape m_borders;
};

}  // namespace GUI

#endif // BUTTON_HPP_
