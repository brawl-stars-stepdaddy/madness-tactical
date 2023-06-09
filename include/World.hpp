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
#include "GameLogic.hpp"
#include "Camera.hpp"
#include "Unit.hpp"

struct Map;
struct CollisionEventListener;
struct DestructionEventListener;

struct World {
public:
    enum Layer {
        BACKGROUND,
        MAP,
        ENTITIES,
        LAYER_COUNT,
    };

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

    FontHolder &get_font_holder() {
        return m_fonts;
    }

    Unit *get_player() {
        return m_active_unit;
    }

    void go_to_next_team();
    void go_to_next_unit();

    SceneNode *get_layer(Layer layer) {
        return m_scene_layers[layer];
    }

    void add_entity(std::unique_ptr<Entity>);

    static constexpr float SCALE = 100.f;

private:
    void load_resources();
    void build_scene();

    sf::RenderWindow &m_window;
    sf::View m_world_view;
    TextureHolder m_textures;
    FontHolder m_fonts;
    SceneNode m_scene_graph;
    std::array<SceneNode *, LAYER_COUNT> m_scene_layers;

    sf::FloatRect m_world_bounds;
    sf::Vector2f m_spawn_position;
    Unit *m_active_unit;
    b2World m_physics_world;
    Map *m_map;
    CollisionEventListener *m_collision_listener;
    DestructionEventListener *m_destruction_listener;
    GameLogic m_game_logic;
    Camera m_camera;
    TeamManager m_team_manager;

    float m_moves_timer = 5;

};

#endif
