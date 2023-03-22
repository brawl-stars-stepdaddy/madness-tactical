#include <Map.hpp>

Map::Map(b2World *world, const std::vector<std::vector<std::pair<float, float>>> &chains_)
    : m_body(MapBody(world, chains_)) {
}

void Map::apply_weapon_effect(const WeaponEffect &weapon_effect) {
    m_body.apply_weapon_effect(weapon_effect);

    // TODO: make shaders
}

void Map::draw_current(sf::RenderTarget &target, sf::RenderStates states) {
    for (const auto &sprite : m_sprites) {
        target.draw(sprite, states);
    }
}
