#ifndef MAP_BODY_HPP_
#define MAP_BODY_HPP_

#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include "WeaponEffect.hpp"

struct MapBody : Body {
public:
    explicit MapBody(b2World *, const std::vector<std::vector<std::pair<float, float>>> &);

    [[nodiscard]] std::vector<sf::ConvexShape> get_triangulation() const;

    void apply_weapon_effect(const WeaponEffect &);
private:
    b2Body *m_body;
    std::vector<std::vector<b2Vec2>> m_chains;
    Clipper2Lib::PathsD m_paths;
};

#endif //MAP_BODY_HPP_
