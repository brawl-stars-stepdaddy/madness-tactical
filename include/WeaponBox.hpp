#ifndef WEAPON_BOX_HPP_
#define WEAPON_BOX_HPP_

#include "Box.hpp"
#include "Weapon.hpp"

struct WeaponBox : Box {
    WeaponBox(World &, sf::FloatRect);
    void on_collision(Entity *) override;
};

#endif  // WEAPON_BOX_HPP_
