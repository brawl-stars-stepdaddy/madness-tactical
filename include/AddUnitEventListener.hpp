#ifndef ADD_UNIT_EVENT_LISTENER_HPP_
#define ADD_UNIT_EVENT_LISTENER_HPP_

#include "AddUnitEventData.hpp"
#include "EventListener.hpp"

struct World;

struct AddUnitEventListener : EventListener {
public:
    explicit AddUnitEventListener(World &world);

    void process(const EventData &event) override;

private:
    World *m_world;
};

#endif // ADD_UNIT_EVENT_LISTENER_HPP_
