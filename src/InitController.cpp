#include "InitController.hpp"
#include "ActionEventData.hpp"
#include "EventManager.hpp"
#include "AddUnitEventData.hpp"
#include "GameState.hpp"

InitController::InitController(GameState &game_state)
        : m_game_state(&game_state) {
    assign_key(
            EventType::CAMERA_MOVE_LEFT, sf::Keyboard::Left,
            ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
            EventType::CAMERA_MOVE_RIGHT, sf::Keyboard::Right,
            ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
            EventType::CAMERA_MOVE_UP, sf::Keyboard::Up,
            ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
            EventType::CAMERA_MOVE_DOWN, sf::Keyboard::Down,
            ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
            EventType::ZOOM_IN, sf::Keyboard::Equal,
            ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
            EventType::ZOOM_OUT, sf::Keyboard::Hyphen,
            ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
            EventType::ADD_UNIT, sf::Keyboard::Space,
            ActionActivationType::ON_KEY_RELEASED
    );

    m_action_binding[EventType::CAMERA_MOVE_LEFT] = [this]() {
        m_game_state->get_event_manager()->queue_event(
                std::make_unique<CameraMoveLeftEventData>()
        );
    };
    m_action_binding[EventType::CAMERA_MOVE_RIGHT] = [this]() {
        m_game_state->get_event_manager()->queue_event(
                std::make_unique<CameraMoveRightEventData>()
        );
    };
    m_action_binding[EventType::CAMERA_MOVE_UP] = [this]() {
        m_game_state->get_event_manager()->queue_event(
                std::make_unique<CameraMoveUpEventData>()
        );
    };
    m_action_binding[EventType::CAMERA_MOVE_DOWN] = [this]() {
        m_game_state->get_event_manager()->queue_event(
                std::make_unique<CameraMoveDownEventData>()
        );
    };
    m_action_binding[EventType::ZOOM_IN] = [this]() {
        m_game_state->get_event_manager()->queue_event(
                std::make_unique<ZoomInEventData>()
        );
    };
    m_action_binding[EventType::ZOOM_OUT] = [this]() {
        m_game_state->get_event_manager()->queue_event(
                std::make_unique<ZoomOutEventData>()
        );
    };
    m_action_binding[EventType::ADD_UNIT] = [this]() {
        m_game_state->get_event_manager()->queue_event(
                std::make_unique<AddUnitEventData>()
        );
    };
}

