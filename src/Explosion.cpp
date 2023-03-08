#include "Explosion.hpp"

Explosion::Explosion(b2Vec2 coordinates_, float radius_) :
        coordinates(coordinates_.x, coordinates_.y),
        radius(radius_) {
}

[[nodiscard]] std::pair<float, float> Explosion::get_coordinates() const {
    return coordinates;
}

[[nodiscard]] float Explosion::get_radius() const {
    return radius;
}
