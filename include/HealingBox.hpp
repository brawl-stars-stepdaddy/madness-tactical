#ifndef HEALING_BOX_HPP_
#define HEALING_BOX_HPP_

#include "Box.hpp"
#include "Weapon.hpp"

struct HealingBox : Box {
    HealingBox(World &, sf::FloatRect);
    void on_collision(Entity *) override;
};

#endif  // HEALING_BOX_HPP_
