#ifndef INIT_CONTROLLER_HPP_
#define INIT_CONTROLLER_HPP_

#include "Controller.hpp"

struct GameState;

struct InitController : Controller {
public:
    explicit InitController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif // INIT_CONTROLLER_HPP_
