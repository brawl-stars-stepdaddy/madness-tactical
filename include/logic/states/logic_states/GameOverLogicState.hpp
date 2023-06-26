#ifndef GAME_OVER_LOGIC_STATE_HPP_
#define GAME_OVER_LOGIC_STATE_HPP_

#include "logic/controllers/Controller.hpp"
#include "logic/states/GameState.hpp"

struct GameOverLogicState : State {
public:
    GameOverLogicState(
        StateStack &stack,
        Context context,
        GameState &game_state
    );
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    GameState *m_game_state;
    sf::Text m_endgame_text;
};

#endif  // GAME_OVER_LOGIC_STATE_HPP_
