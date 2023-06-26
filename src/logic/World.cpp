#include "logic/World.hpp"
#include "game_objects/SpriteNode.hpp"
#include "game_objects/entities/Map.hpp"
#include "game_objects/entities/PlanetCore.hpp"
#include "game_objects/entities/Unit.hpp"
#include "game_objects/weapons/ArmageddonProcess.hpp"
#include "game_objects/weapons/Bazooka.hpp"
#include "logic/events/event_listeners/ActionEventListener.hpp"
#include "logic/events/event_listeners/AddUnitEventListener.hpp"
#include "logic/events/event_listeners/CollisionEventListener.hpp"
#include "logic/events/event_listeners/DestructionEventListener.hpp"
#include "logic/events/event_listeners/ExplosionEventListener.hpp"
#include "logic/events/event_listeners/GameOverEventListener.hpp"
#include "utils/MapGenerator.hpp"
#include "utils/ResourceHolder.hpp"

World::World(
    State &game_state,
    State::Context &context,
    EventManager &event_manager,
    TeamManager &team_manager
)
    : m_game_state(&game_state),
      m_context(context),
      m_event_manager(&event_manager),
      m_team_manager(&team_manager),
      m_world_view(context.window->getDefaultView()),
      m_world_bounds(-200, -200, 400, 400),
      m_physics_world({0, 0}),
      m_camera(nullptr),
      m_scene_graph(*this) {
    load_resources();
    m_event_manager->add_listener(
        std::make_unique<ExplosionEventListener>(), EventType::EXPLOSION
    );
    auto collision_listener = std::make_unique<CollisionEventListener>(*this);
    m_collision_listener = collision_listener.get();
    m_event_manager->add_listener(
        std::move(collision_listener), EventType::COLLISION
    );
    auto destruction_listener = std::make_unique<DestructionEventListener>();
    m_destruction_listener = destruction_listener.get();
    m_event_manager->add_listener(
        std::move(destruction_listener), EventType::DESTRUCTION
    );
    m_event_manager->add_listener(
        std::make_unique<MoveRightEventListener>(*this),
        EventType::MOVE_RIGHT
    );
    m_event_manager->add_listener(
        std::make_unique<MoveLeftEventListener>(*this),
        EventType::MOVE_LEFT
    );
    m_event_manager->add_listener(
        std::make_unique<ChangeAngleUpEventListener>(*this),
        EventType::CHANGE_ANGLE_UP
    );
    m_event_manager->add_listener(
        std::make_unique<ChangeAngleDownEventListener>(*this),
        EventType::CHANGE_ANGLE_DOWN
    );
    m_event_manager->add_listener(
        std::make_unique<JumpForwardEventListener>(*this),
        EventType::JUMP_FORWARD
    );
    m_event_manager->add_listener(
        std::make_unique<JumpBackwardEventListener>(*this),
        EventType::JUMP_BACKWARD
    );
    m_event_manager->add_listener(
        std::make_unique<BeginChargeWeaponEventListener>(*this),
        EventType::BEGIN_CHARGE_WEAPON
    );
    m_event_manager->add_listener(
        std::make_unique<LaunchProjectileEventListener>(*this),
        EventType::LAUNCH_PROJECTILE
    );
    m_event_manager->add_listener(
        std::make_unique<ZoomInEventListener>(&m_camera), EventType::ZOOM_IN
    );
    m_event_manager->add_listener(
        std::make_unique<ZoomOutEventListener>(&m_camera), EventType::ZOOM_OUT
    );
    m_event_manager->add_listener(
        std::make_unique<GameOverEventListener>(), EventType::GAME_OVER
    );
    m_event_manager->add_listener(
        std::make_unique<CameraMoveLeftEventListener>(&m_camera),
        EventType::CAMERA_MOVE_LEFT
    );
    m_event_manager->add_listener(
        std::make_unique<CameraMoveRightEventListener>(&m_camera),
        EventType::CAMERA_MOVE_RIGHT
    );
    m_event_manager->add_listener(
        std::make_unique<CameraMoveUpEventListener>(&m_camera),
        EventType::CAMERA_MOVE_UP
    );
    m_event_manager->add_listener(
        std::make_unique<CameraMoveDownEventListener>(&m_camera),
        EventType::CAMERA_MOVE_DOWN
    );
    m_event_manager->add_listener(
        std::make_unique<AddUnitEventListener>(*this), EventType::ADD_UNIT
    );
}

void World::load_resources() const {
    m_context.textures->load(TexturesID::BACKGROUND, "res/star_sky.jpg");
    m_context.textures->load(TexturesID::MAP_TEXTURE, "res/dirt.jpg");
    m_context.textures->load(TexturesID::UNIT, "res/wheel_amogus.png");
    m_context.textures->load(TexturesID::CANON_BALL, "res/canon_ball.png");
    m_context.textures->load(TexturesID::WEAPON_BOX, "res/weapon_box.png");
    m_context.textures->load(TexturesID::HEALING_BOX, "res/healing_box.png");
    m_context.textures->load(TexturesID::BAZOOKA, "res/bazooka.png");
    m_context.textures->load(TexturesID::GRENADE, "res/grenade.png");
    m_context.textures->load(TexturesID::PLANET_CORE, "res/planet_core.png");
    m_context.textures->load(TexturesID::LAND_MINE, "res/landmine.png");
    m_context.textures->load(TexturesID::LASER, "res/laser.png");
    m_context.textures->load(TexturesID::KETTLEBELL, "res/kettlebell.png");
    m_context.textures->load(TexturesID::CASE, "res/case.png");
    m_context.textures->load(TexturesID::METEORITE, "res/meteorite.png");
    m_context.textures->get(TexturesID::MAP_TEXTURE).setRepeated(true);
    m_context.textures->get(TexturesID::BACKGROUND).setRepeated(true);
}

void World::build_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        auto layer = std::make_shared<SceneNode>(*this);
        m_scene_layers[i] = layer;
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(
            *this, m_context.textures->get(TexturesID::BACKGROUND),
            sf::IntRect(
                static_cast<int>(m_world_bounds.left * World::SCALE),
                static_cast<int>(m_world_bounds.top * World::SCALE),
                static_cast<int>(m_world_bounds.width * World::SCALE),
                static_cast<int>(m_world_bounds.height * World::SCALE)
            )
        );
    background_sprite->setPosition(
        m_world_bounds.left * World::SCALE, m_world_bounds.top * World::SCALE
    );
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));

    std::unique_ptr<PlanetCore> core = std::make_unique<PlanetCore>(*this, 10);
    m_scene_layers[ENTITIES]->attach_child(std::move(core));

    std::shared_ptr<Map> map = std::make_shared<Map>(*this, MapGenerator(1000).get_chains());
    m_scene_layers[MAP]->attach_child(std::move(map));

    m_camera = Camera({0, 0}, 2);
}

void World::build_start_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        auto layer = std::make_shared<SceneNode>(*this);
        m_scene_layers[i] = layer;
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(
            *this, m_context.textures->get(TexturesID::BACKGROUND),
            sf::IntRect(
                static_cast<int>(m_world_bounds.left * World::SCALE),
                static_cast<int>(m_world_bounds.top * World::SCALE),
                static_cast<int>(m_world_bounds.width * World::SCALE),
                static_cast<int>(m_world_bounds.height * World::SCALE)
            )
        );
    background_sprite->setPosition(
        m_world_bounds.left * World::SCALE, m_world_bounds.top * World::SCALE
    );
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));

    std::unique_ptr<PlanetCore> core = std::make_unique<PlanetCore>(*this, 5);
    m_scene_layers[ENTITIES]->attach_child(std::move(core));

    m_camera = Camera({0, 0}, 10);

    std::unique_ptr<Map> map = std::make_unique<Map>(
        *this, MapGenerator(1000, 1, 0.008f, 3.0f, 10.0f, 3).get_chains()
    );
    m_scene_layers[MAP]->attach_child(std::move(map));

    std::unique_ptr<Unit> unit = std::make_unique<Unit>(*this, sf::Vector2f{0, -48}, 5);
    auto body = unit->get_body().get_b2Body();
    body->SetLinearVelocity({14, 0});
    m_scene_layers[ENTITIES]->attach_child(std::move(unit));

    add_process(std::make_unique<ArmageddonProcess>(
        this, 1e9, 3.0f, 100.0f, 1000.0f, 5.0f, 10.0f
    ));
}

void World::draw() {
    m_world_view = m_context.window->getDefaultView();
    m_world_view.setCenter(m_camera.get_offset() * SCALE);
    m_world_view.zoom(m_camera.get_zoom());
    m_world_view.setRotation(m_camera.get_angle() * 180 / M_PIf);
    m_context.window->setView(m_world_view);
    m_context.window->draw(m_scene_graph);
}

void World::update(sf::Time delta_time) {
    execute_processes(delta_time);
    m_physics_world.Step(delta_time.asSeconds(), 1, 1);
    m_scene_graph.update(delta_time);
    m_collision_listener->reset();
    m_destruction_listener->reset();
    m_camera.update(delta_time);
}

void World::add_entity(std::unique_ptr<Entity> ptr) {
    m_scene_layers[ENTITIES]->attach_child(std::move(ptr));
}

sf::Vector2f World::get_camera_position() const {
    return m_camera.get_offset();
}

void World::add_process(std::unique_ptr<Process> process) {
    m_processes.push_back(std::move(process));
}

void World::execute_processes(sf::Time delta_time) {
    for (auto it = m_processes.begin(); it != m_processes.end(); it++) {
        if (it->get()->update(delta_time)) {
            it = m_processes.erase(it);
            it--;
        }
    }
}

Camera *World::get_camera() {
    return &m_camera;
}

void World::add_bloody_fatality_candidate(Unit *unit) {
    m_bloody_fatality_candidates.push_back(unit);
}

std::vector<Unit *> &World::get_bloody_fatality_candidates() {
    return m_bloody_fatality_candidates;
}

void World::reset_bloody_fatality_candidates() {
    m_bloody_fatality_candidates.clear();
}

State *World::get_game_state() {
    return m_game_state;
}

void World::create_unit() {
    auto position = m_camera.get_offset();

    std::shared_ptr<Unit> unit =
        std::make_shared<Unit>(*this, position, 1);
    m_team_manager->get_active_team(true)->add_unit(unit.get());
    auto weapon = std::make_shared<Bazooka>(*this, unit.get());
    m_scene_layers[ENTITIES]->attach_child(unit);
    unit->attach_child(weapon);

    m_team_manager->move_transition(true);
}
