#ifndef MADNESS_TACTICAL_MAP_HPP
#define MADNESS_TACTICAL_MAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include <polypartition.h>
#include "Explosion.hpp"

struct Map {
public:
    explicit Map(b2World *, const std::vector<std::vector<std::pair<float, float>>> &);

    [[nodiscard]] std::vector<sf::ConvexShape> get_triangulation() const;

    void apply_explosion(const Explosion &);

private:
    b2Body *body;
    std::vector<std::vector<b2Vec2>> chains;
    Clipper2Lib::PathsD paths;

};

#endif //MADNESS_TACTICAL_MAP_HPP
