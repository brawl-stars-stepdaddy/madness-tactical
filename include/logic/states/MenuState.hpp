#ifndef MENU_STATE_HPP_
#define MENU_STATE_HPP_

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "gui/Container.hpp"
#include "logic/World.hpp"

struct MenuState : State {
public:
    MenuState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

private:
    GUI::Container m_gui_container;
    EventManager m_event_manager;
    TeamManager m_team_manager;
    World m_background_world;
    sf::Sprite m_game_title_sprite;

    sf::Time m_current_time = sf::Time::Zero;
};

#endif // MENU_STATE_HPP_
