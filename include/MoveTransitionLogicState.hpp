#ifndef MOVE_TRANSITION_LOGIC_STATE_HPP_
#define MOVE_TRANSITION_LOGIC_STATE_HPP_

#include "GameState.hpp"
#include "Controller.hpp"

struct MoveTransitionLogicState : State {
public:
    MoveTransitionLogicState(StateStack &stack, Context context, GameState &game_state);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    sf::Time m_timer = sf::seconds(5);
    GameState *m_game_state;
    float m_box_fall_distance = 100.0f;
    float m_box_fall_impulse = -0.1f;
};

#endif // MOVE_TRANSITION_LOGIC_STATE_HPP_
