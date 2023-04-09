#include "World.hpp"
#include <iostream>
#include <vector>
#include "EventManager.hpp"
#include "EventType.hpp"
#include "Explosion.hpp"
#include "ExplosionEventData.hpp"
#include "ExplosionEventListener.hpp"
#include "SpriteNode.hpp"
#include "Unit.hpp"

World::World(sf::RenderWindow &window)
    : m_window(window),
      m_world_view(window.getDefaultView()),
      m_world_bounds(0.f, 0.f, 20.f, m_world_view.getSize().y),
      m_spawn_position(5.f, 5.f),
      m_player_engineer(nullptr),
      m_physics_world({0, 10}),
      m_map(nullptr) {
    load_textures();
    build_scene();
    EventManager::get()->add_listener(
        std::make_unique<ExplosionEventListener>(this), EventType::EXPLOSION
    );
    EventManager::get()->queue_event(
        std::make_unique<ExplosionEventData>(Explosion({5, 6}, 2))
    );
}

void World::load_textures() {
    m_textures.load(TexturesID::BACKGROUND, "res/bg.png");
    m_textures.load(TexturesID::ENGINEER, "res/Engineer.jpg");
    m_textures.load(TexturesID::HALO, "res/HaloRender.jpg");
    m_textures.load(TexturesID::MAP_TEXTURE, "res/dirt.jpg");
    m_textures.load(TexturesID::WORM, "res/Worm.jpg");
    m_textures.get(TexturesID::MAP_TEXTURE).setRepeated(true);
}

void World::build_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        m_scene_layers[i] = layer.get();
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(m_textures.get(TexturesID::BACKGROUND));
    background_sprite->setPosition(m_world_bounds.left, m_world_bounds.top);
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));
    std::unique_ptr<Unit> engie =
        std::make_unique<Unit>(Unit::Type::WORM, *this, sf::Vector2f{1, 1}, 1);
    m_player_engineer = engie.get();
    m_scene_layers[ENTITIES]->attach_child(std::move(engie));
    std::unique_ptr<SpriteNode> halo =
        std::make_unique<SpriteNode>(m_textures.get(TexturesID::HALO));
    sf::FloatRect bounds = halo->get_sprite().getLocalBounds();
    halo->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    halo->setPosition(-20, -120);
    halo->setScale({0.4, 0.4});
    m_player_engineer->attach_child(std::move(halo));
    m_player_engineer->setRotation(1);
    b2Body *body = m_player_engineer->get_body().get_b2Body();
    // body->SetLinearVelocity({3, 0});
    // body->SetAngularVelocity(1);
    std::unique_ptr<Map> map = std::make_unique<Map>(
        *this,
        std::vector<std::vector<std::pair<float, float>>>{
            {{0, 5}, {5, 6}, {10, 5}, {10, 10}, {0, 10}}}
    );
    m_map = map.get();
    m_scene_layers[MAP]->attach_child(std::move(map));
}

void World::draw() {
    m_window.setView(m_world_view);
    m_window.draw(m_scene_graph);
}

void World::update(sf::Time delta_time) {
    EventManager::get()->update();
    m_physics_world.Step(delta_time.asSeconds(), 1, 1);
    m_scene_graph.update(delta_time);
}