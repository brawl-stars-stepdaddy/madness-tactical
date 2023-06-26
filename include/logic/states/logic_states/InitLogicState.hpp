#ifndef INIT_LOGIC_STATE_HPP_
#define INIT_LOGIC_STATE_HPP_

#include "logic/controllers/Controller.hpp"
#include "logic/states/GameState.hpp"

struct InitLogicState : State {
public:
    InitLogicState(StateStack &stack, Context context, GameState &game_state);

    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    const std::array<sf::Color, 6> m_colors = {
        sf::Color::Red,    sf::Color::Blue, sf::Color::Green,
        sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta};

    std::unique_ptr<Controller> m_controller = nullptr;
    GameState *m_game_state;
    int m_team_number = 3;
    int m_team_size = 3;
    int m_current_unit_number = 0;
};

#endif  // INIT_LOGIC_STATE_HPP_
