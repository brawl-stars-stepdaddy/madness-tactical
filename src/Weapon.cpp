#include "Weapon.hpp"

Weapon::Weapon(World &world) : SceneNode(world) {}

void Weapon::set_hidden(bool new_value) {
    m_is_hidden = new_value;
}
