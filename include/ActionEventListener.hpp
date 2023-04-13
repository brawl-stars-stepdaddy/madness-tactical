#ifndef MADNESS_TACTICAL_ACTIONEVENTLISTENER_HPP
#define MADNESS_TACTICAL_ACTIONEVENTLISTENER_HPP

#include "EventListener.hpp"

struct GameLogic;

struct ChangeAngleDownEventListener : EventListener {
public:
    explicit ChangeAngleDownEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
};

struct ChangeAngleUpEventListener : EventListener {
public:
    explicit ChangeAngleUpEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
};

struct MoveLeftEventListener : EventListener {
public:
    explicit MoveLeftEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
};

struct MoveRightEventListener : EventListener {
public:
    explicit MoveRightEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
};

struct JumpForwardEventListener : EventListener {
public:
    explicit JumpForwardEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
};

struct JumpBackwardEventListener : EventListener {
public:
    explicit JumpBackwardEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
};

struct BeginChargeWeaponEventListener : EventListener {
public:
    explicit BeginChargeWeaponEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
};

struct LaunchProjectileEventListener : EventListener {
public:
    explicit LaunchProjectileEventListener(GameLogic *game_logic);
    void process(const EventData &event) override;

private:
    GameLogic *m_game_logic;
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
