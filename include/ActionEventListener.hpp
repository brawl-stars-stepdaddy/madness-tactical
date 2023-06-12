#ifndef MADNESS_TACTICAL_ACTIONEVENTLISTENER_HPP
#define MADNESS_TACTICAL_ACTIONEVENTLISTENER_HPP

#include "EventListener.hpp"

struct GameLogic;
struct World;

struct ActionEventListener : EventListener {
public:
    ActionEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override = 0;
    virtual ~ActionEventListener() = default;

protected:
    World *m_world;
    GameLogic *m_game_logic;
};

struct ChangeAngleDownEventListener : ActionEventListener {
public:
    ChangeAngleDownEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct ChangeAngleUpEventListener : ActionEventListener {
public:
    ChangeAngleUpEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct MoveLeftEventListener : ActionEventListener {
public:
    MoveLeftEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct MoveRightEventListener : ActionEventListener {
public:
    MoveRightEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct JumpForwardEventListener : ActionEventListener {
public:
    JumpForwardEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct JumpBackwardEventListener : ActionEventListener {
public:
    JumpBackwardEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct BeginChargeWeaponEventListener : ActionEventListener {
public:
    BeginChargeWeaponEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct LaunchProjectileEventListener : ActionEventListener {
public:
    LaunchProjectileEventListener(World &world, GameLogic &game_logic);
    void process(const EventData &event) override;
};

struct Camera;

struct ZoomInEventListener : EventListener {
public:
    explicit ZoomInEventListener(Camera *camera);
    void process(const EventData &event) override;

private:
    Camera *m_camera;
};

struct ZoomOutEventListener : EventListener {
public:
    explicit ZoomOutEventListener(Camera *camera);
    void process(const EventData &event) override;

private:
    Camera *m_camera;
};

#endif //MADNESS_TACTICAL_ACTIONEVENTLISTENER_HPP
