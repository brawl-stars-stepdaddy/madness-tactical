#include "Map.hpp"

Map::Map(
    World &world,
    const std::vector<std::vector<std::pair<float, float>>> &chains
)
    : Entity(world),
      m_body(MapBody(this, m_world->get_physics_world(), chains)) {
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
            &m_world->get_texture_holder().get(TexturesID::MAP_TEXTURE)
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

void Map::update_current(sf::Time delta_time) {}

MapBody &Map::get_body() {
    return m_body;
}

EntityType Map::get_type() {
    return EntityType::MAP;
}

void Map::on_collision(Entity *) {
}

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
    sf::FloatRect bounds = circle.getGlobalBounds();
    circle.setTextureRect(sf::IntRect(
        static_cast<int>(bounds.left), static_cast<int>(bounds.top),
        static_cast<int>(bounds.width), static_cast<int>(bounds.height)
    ));
    circle.setTexture(&m_world->get_texture_holder().get(TexturesID::BACKGROUND)
    );
    m_explosions.emplace_back(circle);
    // TODO: make shaders
}
