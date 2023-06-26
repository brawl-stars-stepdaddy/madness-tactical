#ifndef WEAPON_BOX_HPP_
#define WEAPON_BOX_HPP_

#include "Box.hpp"

struct WeaponBox : Box {
public:
    WeaponBox(World &world, sf::FloatRect rect);

    void on_collision(std::shared_ptr<Entity> other_object) override;
};

#endif  // WEAPON_BOX_HPP_
