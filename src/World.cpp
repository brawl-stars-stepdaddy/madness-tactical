#include <iostream>
#include "World.hpp"
#include "SpriteNode.hpp"

World::World(sf::RenderWindow &window)
    : m_window(window),
      m_world_view(window.getDefaultView()),
      m_world_bounds(0.f, 0.f, 2000.f, m_world_view.getSize().y),
      m_spawn_position(500.f, 500.f),
      m_player_engineer(nullptr),
      m_physics_world({0, 10}) {
    load_textures();
    build_scene();
}

void World::load_textures() {
    m_textures.load(TexturesID::BACKGROUND, "res/bg.png");
    m_textures.load(TexturesID::ENGINEER, "res/Engineer.jpg");
    m_textures.load(TexturesID::HALO, "res/HaloRender.jpg");
}

void World::build_scene() {
    for (std::size_t i = 0; i < LAYER_COUNT; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        m_scene_layers[i] = layer.get();
        m_scene_graph.attach_child(std::move(layer));
    }
    std::unique_ptr<SpriteNode> background_sprite = std::make_unique<SpriteNode>(m_textures.get(TexturesID::BACKGROUND));
    background_sprite->setPosition(m_world_bounds.left, m_world_bounds.top);
    m_scene_layers[BACKGROUND]->attach_child(std::move(background_sprite));
    std::unique_ptr<Unit> engie = std::make_unique<Unit>(Unit::Type::ENGINEER, *this, m_textures);
    m_player_engineer = engie.get();
    m_player_engineer->setPosition(m_spawn_position);
    m_scene_layers[ENTITIES]->attach_child(std::move(engie));
    std::unique_ptr<SpriteNode> halo = std::make_unique<SpriteNode>(m_textures.get(TexturesID::HALO));
    sf::FloatRect bounds = halo->get_sprite().getLocalBounds();
    halo->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    halo->setPosition(34, -200);
    halo->setScale({0.7, 0.7});
    m_player_engineer->attach_child(std::move(halo));
    m_player_engineer->setRotation(1);
    b2Body *body = m_player_engineer->get_body().get_b2Body();
    body->SetLinearVelocity({3, 0});
    body->SetAngularVelocity(60);
}

void World::draw() {
    m_window.setView(m_world_view);
    m_window.draw(m_scene_graph);
}

void World::update(sf::Time delta_time) {
    m_physics_world.Step(delta_time.asSeconds(), 1, 1);
    m_scene_graph.update(delta_time);
}