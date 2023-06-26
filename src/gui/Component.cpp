#include "gui/Component.hpp"

namespace GUI {

bool Component::is_selected() const {
    return m_is_selected;
}

void Component::select() {
    m_is_selected = true;
}

void Component::deselect() {
    m_is_selected = false;
}

bool Component::is_active() {
    return m_is_active;
}

void Component::activate() {
    m_is_active = true;
}

void Component::deactivate() {
    m_is_active = false;
}
}  // namespace GUI
