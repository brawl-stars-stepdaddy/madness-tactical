#ifndef INIT_LOGIC_STATE_HPP_
#define INIT_LOGIC_STATE_HPP_

#include "logic/controllers/Controller.hpp"
#include "logic/states/GameState.hpp"

struct InitLogicState : State {
public:
    InitLogicState(StateStack &stack, Context context, GameState &game_state);

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

private:
    const std::array<sf::Color, 6> m_colors = {
        sf::Color::Red,    sf::Color::Blue, sf::Color::Green,
        sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta
    };

    std::unique_ptr<Controller> m_controller = nullptr;
    GameState *m_game_state;
    int m_team_number = 3;
    int m_team_size = 3;
};

#endif  // INIT_LOGIC_STATE_HPP_
