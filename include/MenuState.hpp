#ifndef MADNESS_TACTICAL_MENUSTATE_HPP
#define MADNESS_TACTICAL_MENUSTATE_HPP

#include "State.hpp"
#include "Container.hpp"
#include <SFML/Graphics.hpp>

struct MenuState : State {
public:
    MenuState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    GUI::Container m_gui_container;
};

#endif
