#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

namespace GUI {

struct Component : sf::Drawable, sf::Transformable {
public:
    typedef std::unique_ptr<Component> Ptr;

    Component() = default;
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
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;

    bool m_is_selected = false;
    bool m_is_active = false;
};

}  // namespace GUI

#endif // COMPONENT_HPP_
