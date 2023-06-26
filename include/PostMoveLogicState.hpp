#ifndef POST_MOVE_LOGIC_STATE_HPP_
#define POST_MOVE_LOGIC_STATE_HPP_

#include "GameState.hpp"
#include "Controller.hpp"

struct PostMoveLogicState : State {
public:
    PostMoveLogicState(StateStack &stack, Context context, GameState &game_state);
    virtual void draw() override;
    virtual bool update(sf::Time delta_time) override;
    virtual bool handle_input(const sf::Event &event) override;
    virtual bool handle_realtime_input() override;

private:
    sf::Time m_timer = sf::seconds(5);
    std::unique_ptr<Controller> m_controller = nullptr;
    GameState *m_game_state;
};

#endif // POST_MOVE_LOGIC_STATE_HPP_