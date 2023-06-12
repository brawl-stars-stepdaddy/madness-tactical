#ifndef MADNESS_TACTICAL_GAMECONTROLLER_HPP
#define MADNESS_TACTICAL_GAMECONTROLLER_HPP

#include "Controller.hpp"

struct GameState;

struct GameController : Controller {
public:
    GameController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif
