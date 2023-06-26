#ifndef CONTACT_LISTENER_HPP_
#define CONTACT_LISTENER_HPP_

#include "box2d/box2d.h"

struct World;

struct ContactListener : b2ContactListener {
    ContactListener(World &world);
    void BeginContact(b2Contact *) override;
    void EndContact(b2Contact *) override;

private:
    World *m_world;
};

#endif  // CONTACT_LISTENER_HPP_
