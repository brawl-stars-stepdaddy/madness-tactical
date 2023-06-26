#include "GameState.hpp"
#include "MoveLogicState.hpp"
#include "PostMoveLogicState.hpp"
#include "BloodyFatalityLogicState.hpp"
#include "MoveTransitionLogicState.hpp"
#include "InitLogicState.hpp"
#include "GameOverLogicState.hpp"

GameState::GameState(StateStack &stack, State::Context context)
    : State(stack, context),
      m_world(*this, context, m_event_manager, m_team_manager),
      m_logic_state_stack(context) {
    m_world.build_scene();

    m_logic_state_stack.register_state<InitLogicState, GameState>(StatesID::Init, *this);
    m_logic_state_stack.register_state<MoveLogicState, GameState>(StatesID::Move, *this);
    m_logic_state_stack.register_state<PostMoveLogicState, GameState>(StatesID::PostMove, *this);
    m_logic_state_stack.register_state<BloodyFatalityLogicState, GameState>(StatesID::BloodyFatality, *this);
    m_logic_state_stack.register_state<MoveTransitionLogicState, GameState>(StatesID::MoveTransition, *this);
    m_logic_state_stack.register_state<GameOverLogicState, GameState>(StatesID::GameOver, *this);

    m_logic_state_stack.push_state(StatesID::Init);
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
        request_stack_push(StatesID::Pause);
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
