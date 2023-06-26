#ifndef MADNESS_TACTICAL_MENUSTATE_HPP
#define MADNESS_TACTICAL_MENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "gui/Container.hpp"
#include "logic/World.hpp"

struct MenuState : State {
public:
    MenuState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    GUI::Container m_gui_container;
    EventManager m_event_manager;
    TeamManager m_team_manager;
    World m_background_world;
    sf::Sprite m_game_title_sprite;

    sf::Time m_current_time = sf::Time::Zero;
};

#endif
