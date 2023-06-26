#ifndef GAME_OVER_LOGIC_STATE_HPP_
#define GAME_OVER_LOGIC_STATE_HPP_

#include "logic/controllers/Controller.hpp"
#include "logic/states/GameState.hpp"

struct GameOverLogicState : State {
public:
    GameOverLogicState(StateStack &stack,
                       Context context,
                       GameState &game_state
                       );

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

private:
    GameState *m_game_state;
    sf::Text m_endgame_text;
};

#endif  // GAME_OVER_LOGIC_STATE_HPP_
