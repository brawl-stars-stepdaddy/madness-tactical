#ifndef SCENE_NODE_HPP_
#define SCENE_NODE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

struct SceneNode : sf::Transformable, sf::Drawable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;

    SceneNode();

    void attach_child(Ptr child);
    Ptr detach_child(const SceneNode &node);
    Ptr detach();

    void update(sf::Time delta_time);

    [[nodiscard]] sf::Transform get_world_transform() const;
    [[nodiscard]] sf::Vector2f get_world_position() const;

private:
    std::vector<Ptr> m_children;
    SceneNode *m_parent;

    void draw(sf::RenderTarget &target, sf::RenderStates states)
        const final;
    virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states)
        const;

    virtual void update_current(sf::Time delta_time);
    void update_children(sf::Time delta_time);
};

#endif