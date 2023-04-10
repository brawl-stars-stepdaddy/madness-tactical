#ifndef CONTACT_LISTENER_HPP_
#define CONTACT_LISTENER_HPP_

#include "box2d/box2d.h"

struct ContactListener : b2ContactListener {
    void BeginContact(b2Contact *) override;
    void EndContact(b2Contact *) override;
};

#endif // CONTACT_LISTENER_HPP_
