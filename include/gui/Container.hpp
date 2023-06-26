#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "Component.hpp"

namespace GUI {

struct Container : Component {
public:
    Container();

    void pack(Component::Ptr component);
    bool is_selectable() override;
    void handle_input(const sf::Event &event) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool has_selection() const;
    void select(int index);
    void select_next();
    void select_previous();

    std::vector<Component::Ptr> m_children;
    int m_selected_child;
};

}  // namespace GUI

#endif // CONTAINER_HPP_
