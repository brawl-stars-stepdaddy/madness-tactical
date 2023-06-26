#ifndef PAUSE_STATE_HPP_
#define PAUSE_STATE_HPP_

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "gui/Container.hpp"

struct PauseState : State {
public:
    PauseState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

private:
    GUI::Container m_gui_container;
    sf::Text m_pause_text;
    sf::Time m_text_effect_time;
    bool m_show_text;
};

#endif // PAUSE_STATE_HPP_
