#include <iostream>
#include "Controller.hpp"
#include "EventType.hpp"
#include "EventManager.hpp"
#include "ActionEventData.hpp"

Controller::Controller() {
    m_key_is_pressed_binding[sf::Keyboard::Left] = EventType::MOVE_LEFT;
    m_key_is_pressed_binding[sf::Keyboard::Right] = EventType::MOVE_RIGHT;
    m_key_is_pressed_binding[sf::Keyboard::Up] = EventType::CHANGE_ANGLE_UP;
    m_key_is_pressed_binding[sf::Keyboard::Down] = EventType::CHANGE_ANGLE_DOWN;
    m_key_pressed_binding[sf::Keyboard::Space] = EventType::BEGIN_CHARGE_WEAPON;
    m_key_pressed_binding[sf::Keyboard::Enter] = EventType::JUMP_FORWARD;
    m_key_pressed_binding[sf::Keyboard::BackSpace] = EventType::JUMP_BACKWARD;
    m_key_released_binding[sf::Keyboard::Space] = EventType::LAUNCH_PROJECTILE;

    m_action_activation_type[EventType::MOVE_LEFT] = ActionActivationType::ON_KEY_IS_PRESSED;
    m_action_activation_type[EventType::MOVE_RIGHT] = ActionActivationType::ON_KEY_IS_PRESSED;
    m_action_activation_type[EventType::CHANGE_ANGLE_UP] = ActionActivationType::ON_KEY_IS_PRESSED;
    m_action_activation_type[EventType::CHANGE_ANGLE_DOWN] = ActionActivationType::ON_KEY_IS_PRESSED;
    m_action_activation_type[EventType::BEGIN_CHARGE_WEAPON] = ActionActivationType::ON_KEY_PRESSED;
    m_action_activation_type[EventType::JUMP_FORWARD] = ActionActivationType::ON_KEY_PRESSED;
    m_action_activation_type[EventType::JUMP_BACKWARD] = ActionActivationType::ON_KEY_PRESSED;
    m_action_activation_type[EventType::LAUNCH_PROJECTILE] = ActionActivationType::ON_KEY_RELEASED;

    m_action_binding[EventType::MOVE_LEFT] = [](){ EventManager::get()->queue_event(std::make_unique<MoveLeftEventData>()); };
    m_action_binding[EventType::MOVE_RIGHT] = [](){ EventManager::get()->queue_event(std::make_unique<MoveRightEventData>()); };
    m_action_binding[EventType::CHANGE_ANGLE_UP] = [](){ EventManager::get()->queue_event(std::make_unique<ChangeAngleUpEventData>()); };
    m_action_binding[EventType::CHANGE_ANGLE_DOWN] = [](){ EventManager::get()->queue_event(std::make_unique<ChangeAngleDownEventData>()); };
    m_action_binding[EventType::BEGIN_CHARGE_WEAPON] = [](){ EventManager::get()->queue_event(std::make_unique<BeginChargeWeaponEventData>()); };
    m_action_binding[EventType::JUMP_FORWARD] = [](){ EventManager::get()->queue_event(std::make_unique<JumpForwardEventData>()); };
    m_action_binding[EventType::JUMP_BACKWARD] = [](){ EventManager::get()->queue_event(std::make_unique<JumpBackwardEventData>()); };
    m_action_binding[EventType::LAUNCH_PROJECTILE] = [](){ EventManager::get()->queue_event(std::make_unique<LaunchProjectileEventData>()); };
}

void Controller::handle_event(const sf::Event &event) {
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

void Controller::assign_key(EventType action, sf::Keyboard::Key key) {
    auto found = m_action_activation_type.find(action);
    if (found != m_action_activation_type.end()) {
        switch (found->second) {
            case ActionActivationType::ON_KEY_IS_PRESSED:
                m_key_is_pressed_binding[key] = action;
                break;
            case ActionActivationType::ON_KEY_PRESSED:
                m_key_pressed_binding[key] = action;
                break;
            case ActionActivationType::ON_KEY_RELEASED:
                m_key_released_binding[key] = action;
                break;
        }
    }
}

sf::Keyboard::Key Controller::get_assigned_key(EventType action) const {
    auto found = m_action_activation_type.find(action);
    if (found != m_action_activation_type.end()) {
        const std::map<sf::Keyboard::Key, EventType> *key_binding;
        switch (found->second) {
            case ActionActivationType::ON_KEY_IS_PRESSED:
                key_binding = &m_key_is_pressed_binding;
                break;
            case ActionActivationType::ON_KEY_PRESSED:
                key_binding = &m_key_pressed_binding;
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
