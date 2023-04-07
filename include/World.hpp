#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <SFML/Graphics.hpp>
#include <array>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "Unit.hpp"
#include "box2d/box2d.h"

struct Unit;

struct World {
public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time delta_time);
    void draw();
    b2World &get_physics_world() {
        return m_physics_world;
    }

private:
    void load_textures();
    void build_scene();

    enum Layer {
        BACKGROUND,
        MAP,
        ENTITIES,
        LAYER_COUNT,
    };

    const float SCALE = 100.f;

    sf::RenderWindow &m_window;
    sf::View m_world_view;
    TextureHolder m_textures;
    SceneNode m_scene_graph;
    std::array<SceneNode *, LAYER_COUNT> m_scene_layers;

    sf::FloatRect m_world_bounds;
    sf::Vector2f m_spawn_position;
    Unit *m_player_engineer;
    b2World m_physics_world;
};

#endif
