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

    Unit *get_player() {
        return m_active_unit;
    }

    void activate_next_unit();
    void activate_next_player();
    void remove_playable_unit(int player_id, Unit *unit);

    SceneNode *get_layer(Layer layer) {
        return m_scene_layers[layer];
    }

    void add_entity(std::unique_ptr<Entity>);

    static constexpr float SCALE = 100.f;

private:
    void load_textures();
    void build_scene();

    sf::RenderWindow &m_window;
    sf::View m_world_view;
    TextureHolder m_textures;
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

    std::vector<std::vector<Unit *>> m_playable_units;
    std::vector<int> m_last_active_units;
    int m_current_player = 0;
    int m_players_number = 2;
    int m_units_number = 2;

    float m_moves_timer = 5;

};

#endif
