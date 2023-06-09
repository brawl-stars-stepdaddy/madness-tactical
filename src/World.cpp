#include "World.hpp"
#include <random>
#include <chrono>
#include <vector>
#include "Bazooka.hpp"
#include "CollisionEventListener.hpp"
#include "DestructionEventListener.hpp"
#include "GameOverEventListener.hpp"
#include "EventManager.hpp"
#include "EventType.hpp"
#include "ExplosionEventData.hpp"
#include "ExplosionEventListener.hpp"
#include "MoveTransitionEventListener.hpp"
#include "ActionEventListener.hpp"
#include "ActionEventData.hpp"
#include "SpriteNode.hpp"
#include "WeaponBox.hpp"
#include "HealingBox.hpp"
#include "Unit.hpp"
#include "UnitHealthBar.hpp"

std::vector<std::pair<float, float>> generate_naive_map() {
    std::mt19937 rng((uint32_t) std::chrono::steady_clock::now().time_since_epoch().count());
    std::normal_distribution <float> gen_real (0, 0.4);

    std::vector<std::pair<float, float>> points;
    float prev_y = 8.0f;
    for (int i = 0; i <= 3000; i++) {
        float x = static_cast<float>(i) / 10;
        prev_y += gen_real(rng);
        points.emplace_back(x, prev_y);
    }
    prev_y = 8.0f;
    for (int i = 0; i <= 3000; i++) {
        float cur_y = points[i].second;
        prev_y = prev_y + 0.02 * (cur_y - prev_y);
        points[i].second = prev_y;
    }
    points.emplace_back(300, 100);
    points.emplace_back(0, 100);
    for (int i = 0; i < points.size(); i++) {
        points[i].first -= 150;
    }
    return points;
}

World::World(sf::RenderWindow &window)
    : m_window(window),
      m_world_view(window.getDefaultView()),
      m_world_bounds(-150, -30, 300, 100),
      m_spawn_position(5.f, 5.f),
      m_active_unit(nullptr),
      m_physics_world({0, 20}),
      m_map(nullptr),
      m_game_logic(this),
      m_camera(nullptr) {
    load_resources();
    build_scene();
    EventManager::get()->add_listener(
        std::make_unique<ExplosionEventListener>(), EventType::EXPLOSION
    );
    auto listener = std::make_unique<CollisionEventListener>(this);
    m_collision_listener = listener.get();
    EventManager::get()->add_listener(std::move(listener), EventType::COLLISION);
    auto destruction_listener = std::make_unique<DestructionEventListener>();
    m_destruction_listener = destruction_listener.get();
    EventManager::get()->add_listener(std::move(destruction_listener), EventType::DESTRUCTION);
    EventManager::get()->add_listener(std::make_unique<MoveRightEventListener>(&m_game_logic), EventType::MOVE_RIGHT);
    EventManager::get()->add_listener(std::make_unique<MoveLeftEventListener>(&m_game_logic), EventType::MOVE_LEFT);
    EventManager::get()->add_listener(std::make_unique<ChangeAngleUpEventListener>(&m_game_logic), EventType::CHANGE_ANGLE_UP);
    EventManager::get()->add_listener(std::make_unique<ChangeAngleDownEventListener>(&m_game_logic), EventType::CHANGE_ANGLE_DOWN);
    EventManager::get()->add_listener(std::make_unique<JumpForwardEventListener>(&m_game_logic), EventType::JUMP_FORWARD);
    EventManager::get()->add_listener(std::make_unique<JumpBackwardEventListener>(&m_game_logic), EventType::JUMP_BACKWARD);
    EventManager::get()->add_listener(std::make_unique<BeginChargeWeaponEventListener>(&m_game_logic), EventType::BEGIN_CHARGE_WEAPON);
    EventManager::get()->add_listener(std::make_unique<LaunchProjectileEventListener>(&m_game_logic),EventType::LAUNCH_PROJECTILE);
    EventManager::get()->add_listener(std::make_unique<ZoomInEventListener>(&m_camera), EventType::ZOOM_IN);
    EventManager::get()->add_listener(std::make_unique<ZoomOutEventListener>(&m_camera),EventType::ZOOM_OUT);
    EventManager::get()->add_listener(std::make_unique<MoveTransitionEventListener>(this), EventType::MOVE_TRANSITION);
    EventManager::get()->add_listener(std::make_unique<GameOverEventListener>(), EventType::GAME_OVER);
}

void World::load_resources() {
    m_textures.load(TexturesID::BACKGROUND, "res/sky.jpg");
    m_textures.load(TexturesID::ENGINEER, "res/Engineer.jpg");
    m_textures.load(TexturesID::HALO, "res/HaloRender.jpg");
    m_textures.load(TexturesID::MAP_TEXTURE, "res/dirt.jpg");
    m_textures.load(TexturesID::WORM, "res/Worm.png");
    m_textures.load(TexturesID::CANON_BALL, "res/canon_ball.png");
    m_textures.load(TexturesID::WEAPON_BOX, "res/weapon_box.png");
    m_textures.load(TexturesID::HEALING_BOX, "res/healing_box.png");
    m_textures.load(TexturesID::BAZOOKA, "res/bazooka.png");
    m_textures.get(TexturesID::MAP_TEXTURE).setRepeated(true);
    m_textures.get(TexturesID::BACKGROUND).setRepeated(true);

    m_fonts.load(FontsID::BAGEL_FONT, "res/BagelFatOne-Regular.ttf");
}

void World::build_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        m_scene_layers[i] = layer.get();
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(m_textures.get(TexturesID::BACKGROUND), sf::IntRect(m_world_bounds.left * World::SCALE,
                                                                                         m_world_bounds.top * World::SCALE,
                                                                                         m_world_bounds.width * World::SCALE,
                                                                                         m_world_bounds.height * World::SCALE));
    background_sprite->setPosition(m_world_bounds.left * World::SCALE, m_world_bounds.top * World::SCALE);
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));
    m_scene_layers[ENTITIES]->attach_child(std::make_unique<WeaponBox>(*this, sf::FloatRect(20, 1, 1.5, 1)));
    m_scene_layers[ENTITIES]->attach_child(std::make_unique<HealingBox>(*this, sf::FloatRect(15, 1, 1.5, 1)));

    Team *team1 = m_team_manager.create_team(sf::Color(255, 0, 0));
    Team *team2 = m_team_manager.create_team(sf::Color(0, 0, 255));


    std::unique_ptr<Unit> worm1 =
        std::make_unique<Unit>(Unit::Type::WORM, this, sf::Vector2f{1, 1}, 1, 0);
    m_active_unit = worm1.get();
    m_scene_layers[ENTITIES]->attach_child(std::move(worm1));
    team1->add_unit(m_active_unit);
    team1->add_weapon(BAZOOKA);
    auto bazooka = std::make_unique<Bazooka>(this, m_active_unit);
    m_active_unit->attach_child(std::move(bazooka));

    std::unique_ptr<Unit> worm2 =
            std::make_unique<Unit>(Unit::Type::WORM, this, sf::Vector2f{10, 1}, 1, 1);
    auto second_unit = worm2.get();
    team2->add_unit(second_unit);
    team2->add_weapon(BAZOOKA);
    bazooka = std::make_unique<Bazooka>(this, second_unit);
    second_unit->attach_child(std::move(bazooka));
    m_scene_layers[ENTITIES]->attach_child(std::move(worm2));

    std::unique_ptr<Unit> worm3 =
            std::make_unique<Unit>(Unit::Type::WORM, this, sf::Vector2f{7, 1}, 1, 1);
    auto third_unit = worm3.get();
    team2->add_unit(third_unit);
    team2->add_weapon(BAZOOKA);
    bazooka = std::make_unique<Bazooka>(this, third_unit);
    third_unit->attach_child(std::move(bazooka));
    m_scene_layers[ENTITIES]->attach_child(std::move(worm3));

    m_camera = Camera(m_active_unit->get_body().get_position(), 2);
    m_camera.set_follow_strategy(std::make_unique<SmoothFollowStrategy>(&m_camera, m_active_unit, .5f, 3.f));
    std::unique_ptr<Map> map = std::make_unique<Map>(
        this,
        std::vector<std::vector<std::pair<float, float>>> {generate_naive_map()}
    );
    m_map = map.get();
    m_scene_layers[MAP]->attach_child(std::move(map));

    m_active_unit->set_activeness(true);
}

void World::draw() {
    m_world_view = m_window.getDefaultView();
    m_world_view.setCenter(m_camera.get_offset() * SCALE);
    m_world_view.zoom(m_camera.get_zoom());
    m_window.setView(m_world_view);
    m_window.draw(m_scene_graph);
}

void World::update(sf::Time delta_time) {
    m_moves_timer -= delta_time.asSeconds();
    if (m_moves_timer <= 0) {
        EventManager::get()->queue_event(
                std::make_unique<MoveTransitionEventData>(MoveTransitionEventData::TransitionType::OTHER_PLAYER));
        m_moves_timer = 5;
    }
    EventManager::get()->update();
    m_physics_world.Step(delta_time.asSeconds(), 1, 1);
    m_scene_graph.update(delta_time);
    m_camera.update(delta_time);
    m_collision_listener->reset();
    m_destruction_listener->reset();
    m_camera.set_follow_strategy(std::make_unique<SmoothFollowStrategy>(&m_camera, m_active_unit, .5f, 3.f));
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

