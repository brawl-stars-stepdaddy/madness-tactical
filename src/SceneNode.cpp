#include "SceneNode.hpp"
#include <algorithm>
#include <cassert>

SceneNode::SceneNode(World &world) : m_world(&world), m_parent(nullptr) {
}

void SceneNode::attach_child(SceneNode::Ptr child) {
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detach_child(const SceneNode &node) {
    auto found = std::find_if(
        m_children.begin(), m_children.end(),
        [&node](const Ptr &p) { return p.get() == &node; }
    );
    assert(found != m_children.end());
    Ptr res = std::move(*found);
    res->m_parent = nullptr;
    m_children.erase(found);
    return res;
}

SceneNode::Ptr SceneNode::detach() {
    assert(m_parent);
    auto found = std::find_if(
        m_parent->m_children.begin(), m_parent->m_children.end(),
        [this](const Ptr &p) { return p.get() == this; }
    );
    assert(found != m_parent->m_children.end());
    Ptr res = std::move(*found);
    m_parent->m_children.erase(found);
    m_parent = nullptr;
    return res;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    draw_current(target, states);
    for (const Ptr &it : m_children) {
        it->draw(target, states);
    }
}

void SceneNode::draw_current(sf::RenderTarget &target, sf::RenderStates states)
    const {
}

void SceneNode::update(sf::Time delta_time) {
    update_current(delta_time);
    update_children(delta_time);
}

void SceneNode::update_current(sf::Time delta_time) {
}

void SceneNode::update_children(sf::Time delta_time) {
    for (const Ptr &child : m_children) {
        child->update(delta_time);
    }
}

sf::Transform SceneNode::get_world_transform() const {
    sf::Transform transform = getTransform();
    for (const SceneNode *ancestor = this; ancestor != nullptr;
         ancestor = ancestor->m_parent) {
        transform = getTransform() * transform;
    }
    return transform;
}

sf::Vector2f SceneNode::get_world_position() const {
    return get_world_transform() * sf::Vector2f();
}

SceneNode::Ptr SceneNode::get_pointer() {
    auto found = std::find_if(
            m_parent->m_children.begin(), m_parent->m_children.end(),
            [this](const Ptr &p) { return p.get() == this; }
    );
    assert(found != m_parent->m_children.end());
    return *found;
}
