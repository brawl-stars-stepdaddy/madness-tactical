#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <array>
#include "Camera.hpp"
#include "Entity.hpp"
#include "EventManager.hpp"
#include "GameLogic.hpp"
#include "Map.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "Unit.hpp"
#include "Process.hpp"
#include "box2d/box2d.h"

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

    World(State::Context &context, EventManager &event_manager, TeamManager &team_manager);

    void build_scene();
    void build_start_scene();

    void update(sf::Time delta_time);
    void draw();

    b2World &get_physics_world() {
        return m_physics_world;
    }

    sf::Vector2f get_camera_position() const;

    Camera *get_camera();

    Map *get_map() {
        return m_map;
    }

    TextureHolder &get_texture_holder() {
        return *m_context.textures;
    }

    FontHolder &get_font_holder() {
        return *m_context.fonts;
    }

    Unit *get_player() {
        return m_active_unit;
    }

    void set_active_unit(Unit *unit) {
        m_active_unit = unit;
    }

    SceneNode *get_layer(Layer layer) {
        return m_scene_layers[layer];
    }

    void add_entity(std::unique_ptr<Entity>);

    EventManager *get_event_manager() {
        return m_event_manager;
    }

    static constexpr float SCALE = 100.f;

    void add_process(std::unique_ptr<Process>);
    void execute_processes(sf::Time);

protected:
    void load_resources();

    State::Context m_context;
    sf::View m_world_view;
    SceneNode m_scene_graph;
    std::array<SceneNode *, LAYER_COUNT> m_scene_layers;

    sf::FloatRect m_world_bounds;
    Unit *m_active_unit;
    b2World m_physics_world;
    Map *m_map;
    CollisionEventListener *m_collision_listener;
    DestructionEventListener *m_destruction_listener;
    GameLogic m_game_logic;
    Camera m_camera;
    TeamManager *m_team_manager;
    EventManager *m_event_manager;

    std::vector<std::unique_ptr<Process>> m_processes;

    float m_moves_timer = 100;
};

#endif
