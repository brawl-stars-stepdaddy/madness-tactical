#ifndef DESTRUCTION_EVENT_LISTENER_HPP_
#define DESTRUCTION_EVENT_LISTENER_HPP_

#include <set>
#include <cassert>
#include "DestructionEventData.hpp"
#include "EventListener.hpp"

struct DestructionEventListener : EventListener {
public:
    void process(const EventData &event) override;
    void reset();

private:
    std::set<SceneNode *> deleted_objects;
};

#endif  // DESTRUCTION_EVENT_LISTENER_HPP_
