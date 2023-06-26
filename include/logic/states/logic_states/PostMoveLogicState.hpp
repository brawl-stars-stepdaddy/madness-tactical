#ifndef POST_MOVE_LOGIC_STATE_HPP_
#define POST_MOVE_LOGIC_STATE_HPP_

#include "logic/controllers/Controller.hpp"
#include "logic/states/GameState.hpp"

struct PostMoveLogicState : State {
public:
    PostMoveLogicState(StateStack &stack,
                       Context context,
                       GameState &game_state
                       );

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_input(const sf::Event &event) override;
    bool handle_realtime_input() override;

private:
    sf::Time m_timer = sf::seconds(5);
    std::unique_ptr<Controller> m_controller = nullptr;
    GameState *m_game_state;
};

#endif  // POST_MOVE_LOGIC_STATE_HPP_
