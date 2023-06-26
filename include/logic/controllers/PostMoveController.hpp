#ifndef POST_MOVE_CONTROLLER_HPP_
#define POST_MOVE_CONTROLLER_HPP_

#include "Controller.hpp"

struct GameState;

struct PostMoveController : Controller {
public:
    explicit PostMoveController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif  // POST_MOVE_CONTROLLER_HPP_
