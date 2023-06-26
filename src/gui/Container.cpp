#include "gui/Container.hpp"

namespace GUI {

Container::Container() : m_children(), m_selected_child(-1) {}

void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (auto &child : m_children) {
        target.draw(*child, states);
    }
}

bool Container::has_selection() const {
    return m_selected_child >= 0;
}

void Container::select(int index) {
    if (m_children[index]->is_selectable()) {
        if (has_selection()) {
            m_children[m_selected_child]->deselect();
        }
        m_selected_child = index;
        m_children[index]->select();
    }
}

void Container::pack(Component::Ptr component) {
    m_children.push_back(std::move(component));
    if (!has_selection() && m_children.back()->is_selectable()) {
        select(static_cast<int>(m_children.size()) - 1);
    }
}

void Container::handle_input(const sf::Event &event) {
    if (has_selection() && m_children[m_selected_child]->is_active()) {
        m_children[m_selected_child]->handle_input(event);
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) {
            select_previous();
        } else if (event.key.code == sf::Keyboard::Down) {
            select_next();
        } else if (event.key.code == sf::Keyboard::Enter) {
            if (has_selection()) {
                m_children[m_selected_child]->activate();
            }
        }
    }
}

bool Container::is_selectable() {
    return false;
}

void Container::select_next() {
    if (!has_selection()) {
        return;
    }
    int next = m_selected_child;
    do {
        next = static_cast<int>((next + 1) % m_children.size());
    } while (!m_children[next]->is_selectable());
    select(next);
}

void Container::select_previous() {
    if (!has_selection()) {
        return;
    }
    int prev = m_selected_child;
    do {
        prev = static_cast<int>((prev + m_children.size() - 1) % m_children.size());
    } while (!m_children[prev]->is_selectable());
    select(prev);
}

}  // namespace GUI
