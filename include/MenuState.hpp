#ifndef MADNESS_TACTICAL_MENUSTATE_HPP
#define MADNESS_TACTICAL_MENUSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics.hpp>

struct MenuState : State {
public:
    MenuState(StateStack &stack, Context context);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

    void update_option_text();

private:
    enum OptionNames {
        Play,
        Exit,
        Huexit,
        NOptions,
    };

    std::vector<sf::Text> m_options;
    int m_option_index;
};

#endif
