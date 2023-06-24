#ifndef MADNESS_TACTICAL_DEFAULTWEAPONCONTROLLER_HPP
#define MADNESS_TACTICAL_DEFAULTWEAPONCONTROLLER_HPP

#include "Controller.hpp"

struct GameState;

struct DefaultWeaponController : Controller {
public:
    DefaultWeaponController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif
