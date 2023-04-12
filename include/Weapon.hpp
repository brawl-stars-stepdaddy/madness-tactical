#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "Projectile.hpp"
#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"
#include "Unit.hpp"

struct Unit;

struct Weapon : SceneNode {
    virtual void charge(sf::Time) = 0;
    virtual void change_angle(sf::Time, bool) = 0;
    virtual std::unique_ptr<Projectile> launch(World &) = 0;

protected:
    Unit *m_parent;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states)
        const override;
};

#endif  // WEAPON_HPP_
