#ifndef MADNESS_TACTICAL_TITLESTATE_HPP
#define MADNESS_TACTICAL_TITLESTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"

struct TitleState : State {
public:
    TitleState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    sf::Sprite m_background_sprite;

    sf::Time m_time = sf::seconds(5);
};

#endif
