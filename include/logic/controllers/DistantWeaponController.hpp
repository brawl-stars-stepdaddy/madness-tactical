#ifndef DISTANT_WEAPON_CONTROLLER_HPP_
#define DISTANT_WEAPON_CONTROLLER_HPP_

#include "Controller.hpp"

struct GameState;

struct DistantWeaponController : Controller {
public:
    explicit DistantWeaponController(GameState &game_state);

private:
    GameState *m_game_state;
};

#endif // DISTANT_WEAPON_CONTROLLER_HPP_
