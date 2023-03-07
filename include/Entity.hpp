#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "SceneNode.hpp"
#include "Body.hpp"

struct Entity : SceneNode {
protected:
    Body m_body;

private:
    virtual void update_current(sf::Time delta_time);
};

#endif