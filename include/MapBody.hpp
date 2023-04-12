#ifndef MAP_BODY_HPP_
#define MAP_BODY_HPP_

#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include "Explosion.hpp"

struct Map;

struct MapBody : Body {
public:
    explicit MapBody(Map *, b2World &, const std::vector<std::vector<std::pair<float, float>>> &);

    [[nodiscard]] std::vector<sf::ConvexShape> get_triangulation() const;

    void apply_explosion(const Explosion &);

    sf::Vector2f get_position() override;
    float get_rotation() override;

private:
    std::vector<std::vector<b2Vec2>> m_chains;
    Clipper2Lib::PathsD m_paths;
};

#endif