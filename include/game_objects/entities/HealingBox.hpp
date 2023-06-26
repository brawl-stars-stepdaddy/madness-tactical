#ifndef HEALING_BOX_HPP_
#define HEALING_BOX_HPP_

#include "Box.hpp"

struct HealingBox : Box {
public:
    HealingBox(World &world, sf::FloatRect rect);

    void on_collision(std::shared_ptr<Entity> other_object) override;
};

#endif  // HEALING_BOX_HPP_
