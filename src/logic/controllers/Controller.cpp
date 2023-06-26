#include "logic/controllers/Controller.hpp"

Controller::Controller() = default;

void Controller::handle_input(const sf::Event &event) {
    EventType action;
    if (event.type == sf::Event::KeyPressed) {
        auto found = m_key_pressed_binding.find(event.key.code);
        if (found == m_key_pressed_binding.end()) {
            return;
        }
        action = found->second;
    } else if (event.type == sf::Event::KeyReleased) {
        auto found = m_key_released_binding.find(event.key.code);
        if (found == m_key_released_binding.end()) {
            return;
        }
        action = found->second;
    } else {
        return;
    }
    m_action_binding[action]();
}

void Controller::handle_realtime_input() {
    for (auto pair : m_key_is_pressed_binding) {
        if (sf::Keyboard::isKeyPressed(pair.first)) {
            m_action_binding[pair.second]();
        }
    }
}

void Controller::assign_key(
    EventType action,
    sf::Keyboard::Key key,
    ActionActivationType action_activation_type
) {
    switch (action_activation_type) {
        case ActionActivationType::ON_KEY_PRESSED:
            m_key_pressed_binding[key] = action;
            m_action_activation_type[action] =
                ActionActivationType::ON_KEY_PRESSED;
            break;
        case ActionActivationType::ON_KEY_IS_PRESSED:
            m_key_is_pressed_binding[key] = action;
            m_action_activation_type[action] =
                ActionActivationType::ON_KEY_IS_PRESSED;
            break;
        case ActionActivationType::ON_KEY_RELEASED:
            m_key_released_binding[key] = action;
            m_action_activation_type[action] =
                ActionActivationType::ON_KEY_RELEASED;
            break;
    }
}

sf::Keyboard::Key Controller::get_assigned_key(EventType action) const {
    auto found = m_action_activation_type.find(action);
    if (found != m_action_activation_type.end()) {
        const std::map<sf::Keyboard::Key, EventType> *key_binding;
        switch (found->second) {
            case ActionActivationType::ON_KEY_PRESSED:
                key_binding = &m_key_pressed_binding;
                break;
            case ActionActivationType::ON_KEY_IS_PRESSED:
                key_binding = &m_key_is_pressed_binding;
                break;
            case ActionActivationType::ON_KEY_RELEASED:
                key_binding = &m_key_released_binding;
                break;
        }
        for (auto pair : *key_binding) {
            if (pair.second == action) {
                return pair.first;
            }
        }
    }
    return sf::Keyboard::Unknown;
}
