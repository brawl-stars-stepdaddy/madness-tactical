#ifndef MADNESS_TACTICAL_GAMESTATE_HPP
#define MADNESS_TACTICAL_GAMESTATE_HPP

#include "EventManager.hpp"
#include "GameController.hpp"
#include "StateStack.hpp"
#include "World.hpp"

struct GameState : State {
public:
    GameState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;
    EventManager *get_event_manager();

private:
    EventManager m_event_manager;
    World m_world;
    GameController m_controller;
};

#endif
