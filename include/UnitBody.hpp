#ifndef UNIT_BODY_HPP_
#define UNIT_BODY_HPP_

#include "Body.hpp"

struct UnitBody : Body {
public:
    explicit UnitBody(b2World &, std::pair<float, float> &);

    sf::Vector2f get_position() override;
    float get_rotation() override;
private:
    b2Body *m_body;
};

#endif //UNIT_BODY_HPP_
