#ifndef MOVE_TRANSITION_LISTENER_HPP_
#define MOVE_TRANSITION_LISTENER_HPP_

#include "EventListener.hpp"
#include "MoveTransitionEventData.hpp"
#include "World.hpp"

struct MoveTransitionEventListener : EventListener {
public:
    explicit MoveTransitionEventListener(World *);
    void process(const EventData &event) override;

private:
    World *m_world;
};

#endif  // MOVE_TRANSITION_LISTENER_HPP_
