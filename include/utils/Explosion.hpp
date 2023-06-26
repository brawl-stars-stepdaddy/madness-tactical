#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include <box2d/box2d.h>

struct Explosion {
public:
    Explosion(b2Vec2, float);

    [[nodiscard]] std::pair<float, float> get_coordinates() const;
    [[nodiscard]] float get_radius() const;

private:
    std::pair<float, float> coordinates;
    float radius;
};

#endif // EXPLOSION_HPP_
