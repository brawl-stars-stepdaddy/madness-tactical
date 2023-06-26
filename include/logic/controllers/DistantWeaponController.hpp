#ifndef MADNESS_TACTICAL_DISTANTWEAPONCONTROLLER_HPP
#define MADNESS_TACTICAL_DISTANTWEAPONCONTROLLER_HPP

#include "Controller.hpp"

struct GameState;

struct DistantWeaponController : Controller {
public:
    explicit DistantWeaponController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif
