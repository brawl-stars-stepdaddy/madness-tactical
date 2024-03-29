#ifndef MADNESS_TACTICAL_CONTROLLER_HPP_
#define MADNESS_TACTICAL_CONTROLLER_HPP_

#include <SFML/Window/Event.hpp>
#include <functional>
#include <map>
#include "logic/events/EventType.hpp"

enum class ControllerStrategy {
    NONE,
    LAUNCH_WEAPON,
    DISTANT_WEAPON
};

struct Controller {
public:
    enum class ActionActivationType {
        ON_KEY_PRESSED,
        ON_KEY_IS_PRESSED,
        ON_KEY_RELEASED,
    };

    Controller();
    void handle_input(const sf::Event &event);
    void handle_realtime_input();
    void
    assign_key(EventType action, sf::Keyboard::Key key, ActionActivationType);
    [[nodiscard]] sf::Keyboard::Key get_assigned_key(EventType action) const;

protected:
    std::map<sf::Keyboard::Key, EventType> m_key_pressed_binding;
    std::map<sf::Keyboard::Key, EventType> m_key_is_pressed_binding;
    std::map<sf::Keyboard::Key, EventType> m_key_released_binding;

    std::map<EventType, ActionActivationType> m_action_activation_type;
    std::map<EventType, std::function<void()>> m_action_binding;
};

#endif  // MADNESS_TACTICAL_CONTROLLER_HPP_
