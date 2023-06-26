#ifndef ACTION_EVENT_LISTENER_HPP_
#define ACTION_EVENT_LISTENER_HPP_

#include "EventListener.hpp"

struct GameLogic;
struct World;

struct ActionEventListener : EventListener {
public:
    explicit ActionEventListener(World &world);
    void process(const EventData &event) override = 0;
    ~ActionEventListener() override = default;

protected:
    World *m_world;
};

struct ChangeAngleDownEventListener : ActionEventListener {
public:
    ChangeAngleDownEventListener(World &world);
    void process(const EventData &event) override;
};

struct ChangeAngleUpEventListener : ActionEventListener {
public:
    ChangeAngleUpEventListener(World &world);
    void process(const EventData &event) override;
};

struct MoveLeftEventListener : ActionEventListener {
public:
    MoveLeftEventListener(World &world);
    void process(const EventData &event) override;
};

struct MoveRightEventListener : ActionEventListener {
public:
    MoveRightEventListener(World &world);
    void process(const EventData &event) override;
};

struct JumpForwardEventListener : ActionEventListener {
public:
    JumpForwardEventListener(World &world);
    void process(const EventData &event) override;
};

struct JumpBackwardEventListener : ActionEventListener {
public:
    JumpBackwardEventListener(World &world);
    void process(const EventData &event) override;
};

struct BeginChargeWeaponEventListener : ActionEventListener {
public:
    BeginChargeWeaponEventListener(World &world);
    void process(const EventData &event) override;
};

struct LaunchProjectileEventListener : ActionEventListener {
public:
    LaunchProjectileEventListener(World &world);
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

struct CameraMoveLeftEventListener : EventListener {
public:
    explicit CameraMoveLeftEventListener(Camera *camera);
    void process(const EventData &event) override;

private:
    Camera *m_camera;
};

struct CameraMoveRightEventListener : EventListener {
public:
    explicit CameraMoveRightEventListener(Camera *camera);
    void process(const EventData &event) override;

private:
    Camera *m_camera;
};

struct CameraMoveUpEventListener : EventListener {
public:
    explicit CameraMoveUpEventListener(Camera *camera);
    void process(const EventData &event) override;

private:
    Camera *m_camera;
};

struct CameraMoveDownEventListener : EventListener {
public:
    explicit CameraMoveDownEventListener(Camera *camera);
    void process(const EventData &event) override;

private:
    Camera *m_camera;
};

#endif // ACTION_EVENT_LISTENER_HPP_
