#ifndef MADNESS_TACTICAL_BUTTON_HPP
#define MADNESS_TACTICAL_BUTTON_HPP

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

    virtual bool is_selectable() override;
    virtual void select() override;
    virtual void deselect() override;
    virtual void activate() override;
    virtual void deactivate() override;

    virtual void handle_input(const sf::Event &event) override;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
        const override;

    Callback m_callback;
    sf::Text m_text;
    sf::RectangleShape m_borders;
};
}  // namespace GUI

#endif
