#include "Map.hpp"

Map::Map(
    World &world,
    const std::vector<std::vector<std::pair<float, float>>> &chains_
)
    : m_body(MapBody(this, world.get_physics_world(), chains_)) {
      m_sprites = m_body.get_triangulation();
    for (auto &triangle : m_sprites) {
        float min_x = triangle.getPoint(0).x * World::SCALE;
        float min_y = triangle.getPoint(0).y * World::SCALE;
        float max_x = triangle.getPoint(0).x * World::SCALE;
        float max_y = triangle.getPoint(0).y * World::SCALE;
        for (int j = 0; j < triangle.getPointCount(); j++) {
            triangle.setPoint(
                j, {triangle.getPoint(j).x * World::SCALE,
                    triangle.getPoint(j).y * World::SCALE}
            );
            min_x = std::min(min_x, triangle.getPoint(j).x);
            min_y = std::min(min_y, triangle.getPoint(j).y);
            max_x = std::max(max_x, triangle.getPoint(j).x);
            max_y = std::max(max_y, triangle.getPoint(j).y);
        }
        triangle.setTextureRect(sf::IntRect(
            static_cast<int>(min_x), static_cast<int>(min_y),
            static_cast<int>(max_x - min_x), static_cast<int>(max_y - min_y)
        ));
        triangle.setTexture(
            &world.get_texture_holder().get(TexturesID::MAP_TEXTURE)
        );
    }
}

void Map::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
    for (const auto &sprite : m_sprites) {
        target.draw(sprite, states);
    }
    for (const auto &sprite : m_explosions) {
        target.draw(sprite, states);
    }
}

MapBody &Map::get_body() {
    return m_body;
}

EntityType Map::get_type() {
    return EntityType::MAP;
}

void Map::on_collision(Entity *) {}

void Map::on_explosion(const Explosion &explosion) {
    m_body.apply_explosion(explosion);
    sf::CircleShape circle(explosion.get_radius() * World::SCALE, 20);
    circle.setOrigin(
            explosion.get_radius() * World::SCALE,
            explosion.get_radius() * World::SCALE
    );
    circle.setPosition(
            explosion.get_coordinates().first * World::SCALE,
            explosion.get_coordinates().second * World::SCALE
    );
    m_explosions.emplace_back(circle);
    // TODO: make shaders
}
