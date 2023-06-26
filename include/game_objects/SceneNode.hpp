#ifndef SCENE_NODE_HPP_
#define SCENE_NODE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

struct World;

struct SceneNode : sf::Transformable, sf::Drawable, private sf::NonCopyable {
public:
    typedef std::shared_ptr<SceneNode> Ptr;

    SceneNode(World &world);

    void attach_child(Ptr child);
    Ptr detach_child(const SceneNode &node);
    Ptr detach();

    void update(sf::Time delta_time);

    [[nodiscard]] sf::Transform get_world_transform() const;
    [[nodiscard]] sf::Vector2f get_world_position() const;

    Ptr get_pointer();

protected:
    World *m_world;

private:
    std::vector<Ptr> m_children;
    SceneNode *m_parent;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
    virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states)
        const;

    virtual void update_current(sf::Time delta_time);
    void update_children(sf::Time delta_time);
};

#endif