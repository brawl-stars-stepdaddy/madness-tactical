#ifndef MADNESS_TACTICAL_COMPONENT_HPP
#define MADNESS_TACTICAL_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace GUI {
struct Component : sf::Drawable, sf::Transformable {
public:
    typedef std::unique_ptr<Component> Ptr;

    Component();
    ~Component() override = default;
    virtual bool is_selectable() = 0;
    bool is_selected() const;
    virtual void select();
    virtual void deselect();
    virtual bool is_active();
    virtual void activate();
    virtual void deactivate();
    virtual void handle_input(const sf::Event &event) = 0;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
        const = 0;

    bool m_is_selected;
    bool m_is_active;
};
}  // namespace GUI

#endif
