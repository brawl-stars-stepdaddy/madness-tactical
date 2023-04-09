#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "Body.hpp"
#include "SceneNode.hpp"

struct Entity : SceneNode {
public:
    virtual Body &get_body() = 0;

private:
    void update_current(sf::Time delta_time) override;

    virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states)
        const override {
    }
};

#endif