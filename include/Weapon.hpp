#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <vector>
#include "Projectile.hpp"
#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"

enum WeaponType {
    BAZOOKA,
    GRENADE,
    CONCRETE_DONKEY
};

const int WEAPON_TYPES_NUMBER = 3;

struct Unit;

struct Weapon : SceneNode {
    virtual void launch(World &) = 0;
    void set_hidden(bool);

protected:
    Unit *m_parent;
    bool m_is_hidden = true;
};

#endif  // WEAPON_HPP_
