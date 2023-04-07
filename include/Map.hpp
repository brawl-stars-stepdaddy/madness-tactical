#ifndef MAP_HPP_
#define MAP_HPP_

#include <box2d/box2d.h>
#include <clipper2/clipper.h>
#include <polypartition.h>
#include "WeaponEffect.hpp"
#include "Entity.hpp"
#include "MapBody.hpp"
#include "World.hpp"

struct Map : Entity {
public:
    explicit Map(World &, const std::vector<std::vector<std::pair<float, float>>> &);

    void apply_weapon_effect(const WeaponEffect &);

    virtual void draw_current(sf::RenderTarget &, sf::RenderStates) final;

    MapBody &get_body() override;

private:
    MapBody m_body;
    std::vector<sf::Sprite> m_sprites;

};

#endif //MAP_HPP_
