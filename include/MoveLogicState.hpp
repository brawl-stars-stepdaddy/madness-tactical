#ifndef MADNESS_TACTICAL_LOGICMOVESTATE_HPP
#define MADNESS_TACTICAL_LOGICMOVESTATE_HPP

#include "GameState.hpp"
#include "Controller.hpp"

struct MoveLogicState : State {
public:
    MoveLogicState(StateStack &stack, Context context, GameState &game_state);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    sf::Time m_timer = sf::seconds(5);
    std::unique_ptr<Controller> m_controller = nullptr;
    GameState *m_game_state;
    sf::Text m_timer_text;
};

#endif
