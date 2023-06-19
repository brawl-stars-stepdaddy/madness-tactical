#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <vector>
#include "Projectile.hpp"
#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"

enum WeaponType { BAZOOKA, LASER, GRENADE, LAND_MINE, CONCRETE_DONKEY };

const int WEAPON_TYPES_NUMBER = 3;

struct Unit;

struct Weapon : SceneNode {
    explicit Weapon(World &world);

    virtual void launch() = 0;
    void set_hidden(bool);

protected:
    Unit *m_parent;
    bool m_is_hidden = true;
};

#endif  // WEAPON_HPP_
