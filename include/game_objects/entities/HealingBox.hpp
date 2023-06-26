#ifndef HEALING_BOX_HPP_
#define HEALING_BOX_HPP_

#include "Box.hpp"
#include "game_objects/weapons/Weapon.hpp"

struct HealingBox : Box {
    HealingBox(World &, sf::FloatRect);
    void on_collision(std::shared_ptr<Entity>) override;
};

#endif  // HEALING_BOX_HPP_
