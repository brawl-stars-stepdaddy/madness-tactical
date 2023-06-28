#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP_

#include "logic/states/StateStack.hpp"
#include "logic/World.hpp"
#include "logic/events/EventManager.hpp"

struct GameState : State {
public:
    GameState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

    EventManager *get_event_manager();
    TeamManager *get_team_manager();
    StateStack *get_logic_state_stack();
    World *get_world();

private:
    EventManager m_event_manager;
    TeamManager m_team_manager;
    World m_world;
    StateStack m_logic_state_stack;
};

#endif // GAME_STATE_HPP_
