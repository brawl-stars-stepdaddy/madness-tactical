#ifndef ARMAGEDDON_HPP_
#define ARMAGEDDON_HPP_

#include "Weapon.hpp"

struct Armageddon : Weapon {
public:
    Armageddon(World &, Unit *);

    void launch() override;
    virtual WeaponControllerType get_controller_type() override;

private:
    void update_current(sf::Time delta_time) override;
    void draw_current(sf::RenderTarget &target, sf::RenderStates states)
        const override;

    sf::Sprite m_sprite;
};

#endif  // ARMAGEDDON_HPP_
