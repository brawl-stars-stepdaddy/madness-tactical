#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include <polypartition.h>
#include "WeaponEffect.hpp"
#include "Entity.hpp"

struct Map : Entity {
public:
    explicit Map(b2World *, const std::vector<std::vector<std::pair<float, float>>> &);

    [[nodiscard]] std::vector<sf::ConvexShape> get_triangulation() const;

    void apply_weapon_effect(const WeaponEffect &);

    virtual void draw_current(sf::RenderTarget &, sf::RenderStates) final;

private:
    b2Body *m_body;
    std::vector<std::vector<b2Vec2>> m_chains;
    Clipper2Lib::PathsD m_paths;

    std::vector<sf::Sprite> m_sprites;

};

#endif //MAP_HPP_
