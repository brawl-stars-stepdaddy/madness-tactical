#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <SFML/Graphics.hpp>
#include <array>
#include "Entity.hpp"
#include "Map.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "box2d/box2d.h"

struct Map;

struct World {
public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time delta_time);
    void draw();

    b2World &get_physics_world() {
        return m_physics_world;
    }

    Map *get_map() {
        return m_map;
    }

    TextureHolder &get_texture_holder() {
        return m_textures;
    }

    static constexpr float SCALE = 100.f;

private:
    void load_textures();
    void build_scene();

    enum Layer {
        BACKGROUND,
        MAP,
        ENTITIES,
        LAYER_COUNT,
    };

    sf::RenderWindow &m_window;
    sf::View m_world_view;
    TextureHolder m_textures;
    SceneNode m_scene_graph;
    std::array<SceneNode *, LAYER_COUNT> m_scene_layers;

    sf::FloatRect m_world_bounds;
    sf::Vector2f m_spawn_position;
    Entity *m_player_engineer;
    b2World m_physics_world;
    Map *m_map;
};

#endif
