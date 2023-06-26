#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <SFML/Graphics.hpp>
#include <array>
#include "GameLogic.hpp"
#include "box2d/box2d.h"
#include "events/EventManager.hpp"
#include "game_objects/SceneNode.hpp"
#include "game_objects/entities/Entity.hpp"
#include "game_objects/entities/Map.hpp"
#include "game_objects/entities/Unit.hpp"
#include "game_objects/weapons/Process.hpp"
#include "states/State.hpp"
#include "utils/Camera.hpp"
#include "utils/ResourceHolder.hpp"
#include "utils/ResourceIdentifiers.hpp"

struct GameState;
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

    World(
        State &game_state,
        State::Context &context,
        EventManager &event_manager,
        TeamManager &team_manager
    );

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

    std::shared_ptr<SceneNode> get_layer(Layer layer) {
        return m_scene_layers[layer];
    }

    void add_entity(std::unique_ptr<Entity>);

    EventManager *get_event_manager() {
        return m_event_manager;
    }

    static constexpr float SCALE = 100.f;

    void add_process(std::unique_ptr<Process>);
    void execute_processes(sf::Time);

    void add_bloody_fatality_candidate(Unit *);
    std::vector<Unit *> &get_bloody_fatality_candidates();
    void reset_bloody_fatality_candidates();

    State *get_game_state();

    void create_unit();

protected:
    void load_resources();

    State *m_game_state;
    State::Context m_context;
    sf::View m_world_view;
    SceneNode m_scene_graph;
    std::array<std::shared_ptr<SceneNode>, LAYER_COUNT> m_scene_layers;

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
    std::vector<Unit *> m_bloody_fatality_candidates;
};

#endif
