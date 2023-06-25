#include "World.hpp"
#include <chrono>
#include <random>
#include <vector>
#include "ActionEventData.hpp"
#include "Armageddon.hpp"
#include "ArmageddonProcess.hpp"
#include "ActionEventListener.hpp"
#include "Bazooka.hpp"
#include "Kettlebell.hpp"
#include "CollisionEventListener.hpp"
#include "DestructionEventListener.hpp"
#include "EventManager.hpp"
#include "EventType.hpp"
#include "ExplosionEventListener.hpp"
#include "GameOverEventListener.hpp"
#include "Grenade.hpp"
#include "HealingBox.hpp"
#include "LandMine.hpp"
#include "Laser.hpp"
#include "MapGenerator.hpp"
#include "MoveTransitionEventListener.hpp"
#include "PlanetCore.hpp"
#include "SpriteNode.hpp"
#include "Unit.hpp"
#include "WeaponBox.hpp"

World::World(State::Context &context, EventManager &event_manager)
    : m_context(context),
      m_event_manager(&event_manager),
      m_world_view(context.window->getDefaultView()),
      m_world_bounds(-200, -200, 400, 400),
      m_spawn_position(5.f, 5.f),
      m_active_unit(nullptr),
      m_physics_world({0, 0}),
      m_map(nullptr),
      m_game_logic(this),
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
        std::make_unique<MoveRightEventListener>(*this, m_game_logic),
        EventType::MOVE_RIGHT
    );
    m_event_manager->add_listener(
        std::make_unique<MoveLeftEventListener>(*this, m_game_logic),
        EventType::MOVE_LEFT
    );
    m_event_manager->add_listener(
        std::make_unique<ChangeAngleUpEventListener>(*this, m_game_logic),
        EventType::CHANGE_ANGLE_UP
    );
    m_event_manager->add_listener(
        std::make_unique<ChangeAngleDownEventListener>(*this, m_game_logic),
        EventType::CHANGE_ANGLE_DOWN
    );
    m_event_manager->add_listener(
        std::make_unique<JumpForwardEventListener>(*this, m_game_logic),
        EventType::JUMP_FORWARD
    );
    m_event_manager->add_listener(
        std::make_unique<JumpBackwardEventListener>(*this, m_game_logic),
        EventType::JUMP_BACKWARD
    );
    m_event_manager->add_listener(
        std::make_unique<BeginChargeWeaponEventListener>(*this, m_game_logic),
        EventType::BEGIN_CHARGE_WEAPON
    );
    m_event_manager->add_listener(
        std::make_unique<LaunchProjectileEventListener>(*this, m_game_logic),
        EventType::LAUNCH_PROJECTILE
    );
    m_event_manager->add_listener(
        std::make_unique<ZoomInEventListener>(&m_camera), EventType::ZOOM_IN
    );
    m_event_manager->add_listener(
        std::make_unique<ZoomOutEventListener>(&m_camera), EventType::ZOOM_OUT
    );
    m_event_manager->add_listener(
        std::make_unique<MoveTransitionEventListener>(this),
        EventType::MOVE_TRANSITION
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
}

void World::load_resources() {
    m_context.textures->load(TexturesID::BACKGROUND, "res/star_sky.jpg");
    m_context.textures->load(TexturesID::ENGINEER, "res/Engineer.jpg");
    m_context.textures->load(TexturesID::HALO, "res/HaloRender.jpg");
    m_context.textures->load(TexturesID::MAP_TEXTURE, "res/dirt.jpg");
    m_context.textures->load(TexturesID::WORM, "res/wheel_amogus.png");
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
        SceneNode::Ptr layer = std::make_unique<SceneNode>(*this);
        m_scene_layers[i] = layer.get();
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(
            *this, m_context.textures->get(TexturesID::BACKGROUND),
            sf::IntRect(
                m_world_bounds.left * World::SCALE,
                m_world_bounds.top * World::SCALE,
                m_world_bounds.width * World::SCALE,
                m_world_bounds.height * World::SCALE
            )
        );
    background_sprite->setPosition(
        m_world_bounds.left * World::SCALE, m_world_bounds.top * World::SCALE
    );
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));
    m_scene_layers[ENTITIES]->attach_child(
        std::make_unique<WeaponBox>(*this, sf::FloatRect(50, -50, 1.5, 1))
    );
    m_scene_layers[ENTITIES]->attach_child(
        std::make_unique<HealingBox>(*this, sf::FloatRect(-50, 50, 1.5, 1))
    );

    Team *team1 = m_team_manager.create_team(sf::Color(255, 0, 0));
    Team *team2 = m_team_manager.create_team(sf::Color(0, 0, 255));

    std::unique_ptr<PlanetCore> core = std::make_unique<PlanetCore>(*this, 10);
    m_scene_layers[ENTITIES]->attach_child(std::move(core));

    std::unique_ptr<Unit> worm1 = std::make_unique<Unit>(
        *this, Unit::Type::WORM, sf::Vector2f{0, 60}, 1, 0
    );
    m_active_unit = worm1.get();
    m_scene_layers[ENTITIES]->attach_child(std::move(worm1));
    team1->add_unit(m_active_unit);
    team1->add_weapon(ARMAGEDDON);
    auto weapon = std::make_unique<Armageddon>(*this, m_active_unit);
    m_active_unit->attach_child(std::move(weapon));

    /*std::unique_ptr<Unit> worm2 =
            std::make_unique<Unit>(*this, Unit::Type::WORM, sf::Vector2f{60, 1},
    1, 1); auto second_unit = worm2.get(); team2->add_unit(second_unit);
    team2->add_weapon(LAND_MINE);
    weapon = std::make_unique<LandMine>(*this, second_unit);
    second_unit->attach_child(std::move(weapon));
    m_scene_layers[ENTITIES]->attach_child(std::move(worm2));*/

    m_camera = Camera(m_active_unit->get_body().get_position(), 2);
    m_camera.set_follow_strategy(std::make_unique<ControlledFollowStrategy>(
        &m_camera
    ));
    std::unique_ptr<Map> map =
        std::make_unique<Map>(*this, MapGenerator(1000).get_chains());
    m_map = map.get();
    m_scene_layers[MAP]->attach_child(std::move(map));

    m_active_unit->set_activeness(true);
}

void World::build_start_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>(*this);
        m_scene_layers[i] = layer.get();
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
            std::make_unique<SpriteNode>(
                    *this, m_context.textures->get(TexturesID::BACKGROUND),
                    sf::IntRect(
                            m_world_bounds.left * World::SCALE,
                            m_world_bounds.top * World::SCALE,
                            m_world_bounds.width * World::SCALE,
                            m_world_bounds.height * World::SCALE
                    )
            );
    background_sprite->setPosition(
            m_world_bounds.left * World::SCALE, m_world_bounds.top * World::SCALE
    );
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));

    std::unique_ptr<PlanetCore> core = std::make_unique<PlanetCore>(*this, 5);
    m_scene_layers[ENTITIES]->attach_child(std::move(core));

    std::unique_ptr<Unit> unit = std::make_unique<Unit>(
            *this, Unit::Type::WORM, sf::Vector2f{0, -48}, 5, 0
    );
    auto body = unit->get_body().get_b2Body();
    body->SetLinearVelocity({14, 0});
    m_scene_layers[ENTITIES]->attach_child(std::move(unit));

    m_camera = Camera({0, 0}, 10);

    std::unique_ptr<Map> map =
            std::make_unique<Map>(*this, MapGenerator(1000, 1, 0.008f, 3.0f, 10.0f, 3).get_chains());
    m_map = map.get();
    m_scene_layers[MAP]->attach_child(std::move(map));

    m_moves_timer = 1e9;

    add_process(std::make_unique<ArmageddonProcess>(this, 1e9, 3.0f, 100.0f, 1000.0f, 5.0f, 10.0f));
}

void World::draw() {
    m_world_view = m_context.window->getDefaultView();
    m_world_view.setCenter(m_camera.get_offset() * SCALE);
    m_world_view.zoom(m_camera.get_zoom());
    m_world_view.setRotation(m_camera.get_angle() * 180 / M_PI);
    m_context.window->setView(m_world_view);
    m_context.window->draw(m_scene_graph);
}

void World::update(sf::Time delta_time) {
    m_moves_timer -= delta_time.asSeconds();
    if (m_moves_timer <= 0) {
        m_event_manager->queue_event(std::make_unique<MoveTransitionEventData>(
            MoveTransitionEventData::TransitionType::OTHER_PLAYER
        ));
        m_moves_timer = 5;
    }
    m_event_manager->update();
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

void World::go_to_next_team() {
    m_team_manager.move_transition();
    m_active_unit = m_team_manager.get_active_team()->get_active_unit();
}

void World::go_to_next_unit() {
    m_active_unit = m_team_manager.get_active_team()->activate_next_unit();
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
