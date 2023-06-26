#include "logic/states/logic_states/WeaponSelectLogicState.hpp"
#include "logic/states/GameState.hpp"
#include "logic/states/logic_states/BloodyFatalityLogicState.hpp"
#include "logic/states/logic_states/GameOverLogicState.hpp"
#include "logic/states/logic_states/InitLogicState.hpp"
#include "logic/states/logic_states/MoveLogicState.hpp"
#include "logic/states/logic_states/MoveTransitionLogicState.hpp"
#include "logic/states/logic_states/PostMoveLogicState.hpp"

GameState::GameState(StateStack &stack, State::Context context)
    : State(stack, context),
      m_world(*this, context, m_event_manager, m_team_manager),
      m_logic_state_stack(context) {
    m_world.build_scene();

    m_logic_state_stack.register_state<InitLogicState, GameState>(
            StatesID::INIT, *this
    );
    m_logic_state_stack.register_state<MoveLogicState, GameState>(
            StatesID::MOVE, *this
    );
    m_logic_state_stack.register_state<PostMoveLogicState, GameState>(
            StatesID::POST_MOVE, *this
    );
    m_logic_state_stack.register_state<BloodyFatalityLogicState, GameState>(
            StatesID::BLOODY_FATALITY, *this
    );
    m_logic_state_stack.register_state<MoveTransitionLogicState, GameState>(
            StatesID::MOVE_TRANSITION, *this
    );
    m_logic_state_stack.register_state<GameOverLogicState, GameState>(
            StatesID::GAME_OVER, *this
    );
    m_logic_state_stack.register_state<WeaponSelectLogicState, GameState>(
            StatesID::WEAPON_SELECT, *this
    );

    m_logic_state_stack.push_state(StatesID::INIT);
}

void GameState::draw() {
    m_world.draw();
    m_logic_state_stack.draw();
}

bool GameState::update(sf::Time delta_time) {
    m_world.update(delta_time);
    m_logic_state_stack.update(delta_time);
    m_event_manager.update();
    return false;
}

bool GameState::handle_input(const sf::Event &event) {
    m_logic_state_stack.handle_input(event);
    if (event.type == sf::Event::KeyReleased &&
        event.key.code == sf::Keyboard::Escape) {
        request_stack_push(StatesID::PAUSE);
    }
    return false;
}

bool GameState::handle_realtime_input() {
    m_logic_state_stack.handle_realtime_input();
    return false;
}

EventManager *GameState::get_event_manager() {
    return &m_event_manager;
}

TeamManager *GameState::get_team_manager() {
    return &m_team_manager;
}

World *GameState::get_world() {
    return &m_world;
}

StateStack *GameState::get_logic_state_stack() {
    return &m_logic_state_stack;
}
