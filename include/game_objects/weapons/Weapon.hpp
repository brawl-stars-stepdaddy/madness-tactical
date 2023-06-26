#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "game_objects/SceneNode.hpp"

enum WeaponType {
    BAZOOKA,
    LASER,
    GRENADE,
    LAND_MINE,
    KETTLEBELL,
    ARMAGEDDON,
    WEAPON_TYPES_NUMBER
};

enum WeaponControllerType { LAUNCH, DISTANT };

struct Unit;

struct Weapon : SceneNode {
public:
    explicit Weapon(World &world);

    virtual void launch();
    virtual WeaponControllerType get_controller_type() = 0;
    void set_hidden(bool value);

protected:
    Unit *m_parent{};
    bool m_is_hidden = true;
};

#endif  // WEAPON_HPP_
