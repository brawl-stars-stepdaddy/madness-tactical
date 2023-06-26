#include "logic/controllers/PostMoveController.hpp"
#include "logic/events/event_data/ActionEventData.hpp"
#include "logic/states/GameState.hpp"

PostMoveController::PostMoveController(GameState &game_state)
    : m_game_state(&game_state) {
    assign_key(
        EventType::MOVE_LEFT, sf::Keyboard::Left,
        ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
        EventType::MOVE_RIGHT, sf::Keyboard::Right,
        ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
        EventType::JUMP_FORWARD, sf::Keyboard::Enter,
        ActionActivationType::ON_KEY_PRESSED
    );
    assign_key(
        EventType::JUMP_BACKWARD, sf::Keyboard::BackSpace,
        ActionActivationType::ON_KEY_PRESSED
    );
    assign_key(
        EventType::ZOOM_IN, sf::Keyboard::Equal,
        ActionActivationType::ON_KEY_IS_PRESSED
    );
    assign_key(
        EventType::ZOOM_OUT, sf::Keyboard::Hyphen,
        ActionActivationType::ON_KEY_IS_PRESSED
    );

    m_action_binding[EventType::MOVE_LEFT] = [this]() {
        m_game_state->get_event_manager()->queue_event(
            std::make_unique<MoveLeftEventData>()
        );
    };
    m_action_binding[EventType::MOVE_RIGHT] = [this]() {
        m_game_state->get_event_manager()->queue_event(
            std::make_unique<MoveRightEventData>()
        );
    };
    m_action_binding[EventType::JUMP_FORWARD] = [this]() {
        m_game_state->get_event_manager()->queue_event(
            std::make_unique<JumpForwardEventData>()
        );
    };
    m_action_binding[EventType::JUMP_BACKWARD] = [this]() {
        m_game_state->get_event_manager()->queue_event(
            std::make_unique<JumpBackwardEventData>()
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
}
