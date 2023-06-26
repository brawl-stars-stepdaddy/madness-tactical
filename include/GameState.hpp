#ifndef MADNESS_TACTICAL_GAMESTATE_HPP
#define MADNESS_TACTICAL_GAMESTATE_HPP

#include "EventManager.hpp"
#include "LaunchWeaponController.hpp"
#include "StateStack.hpp"
#include "World.hpp"
#include "DistantWeaponController.hpp"

struct GameState : State {
public:
    GameState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;
    EventManager *get_event_manager();
    TeamManager *get_team_manager();
    World *get_world();

private:
    EventManager m_event_manager;
    TeamManager m_team_manager;
    World m_world;
    StateStack m_logic_state_stack;
};

#endif
