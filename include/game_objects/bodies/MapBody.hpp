#ifndef MAP_BODY_HPP_
#define MAP_BODY_HPP_

#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include <SFML/Graphics.hpp>
#include "Body.hpp"

struct Explosion;
struct Map;

struct MapBody : Body {
public:
    explicit MapBody(Map *parent, b2World &world,
                     const std::vector<std::vector<std::pair<float, float>>> &chains);

    [[nodiscard]] std::vector<sf::ConvexShape> get_triangulation() const;

    void apply_explosion(const Explosion &explosion);

    [[nodiscard]] sf::Vector2f get_position() const override;
    [[nodiscard]] float get_rotation() const override;

private:
    std::vector<std::vector<b2Vec2>> m_chains;
    Clipper2Lib::PathsD m_paths;
};

#endif // MAP_BODY_HPP_