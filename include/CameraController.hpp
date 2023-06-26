#ifndef CAMERA_CONTROLLER_HPP_
#define CAMERA_CONTROLLER_HPP_

#include <Controller.hpp>

struct GameState;

struct CameraController : Controller {
public:
    explicit CameraController(GameState &game_state);

private:
    GameState *m_game_state;
};


#endif // CAMERA_CONTROLLER_HPP_
