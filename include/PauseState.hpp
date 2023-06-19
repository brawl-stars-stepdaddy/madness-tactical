#ifndef MADNESS_TACTICAL_PAUSESTATE_HPP
#define MADNESS_TACTICAL_PAUSESTATE_HPP

#include "State.hpp"
#include <SFML/Graphics.hpp>

struct PauseState : State {
public:
    PauseState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    sf::Text m_pause_text;
    sf::Time m_text_effect_time;
    bool m_show_text;
};

#endif
