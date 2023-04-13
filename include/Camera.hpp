#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "SFML/Graphics.hpp"
#include <memory>

struct Entity;
struct Camera;

struct FollowStrategy {
public:
    virtual void update(sf::Time delta_time) = 0;

    virtual ~FollowStrategy() = default;
};

struct SmoothFollowStrategy : FollowStrategy {
public:
    SmoothFollowStrategy(Camera *camera, Entity *target, float min_speed, float convergence_factor);

    void update(sf::Time delta_time) override;

private:
    Camera *m_camera;
    Entity *m_target;
    float m_min_speed;
    float m_convergence_factor;
};

struct Camera {
public:
    explicit Camera(std::nullptr_t);

    explicit Camera(sf::Vector2f offset, float zoom);

    void update(sf::Time delta_time);

    [[nodiscard]] sf::Vector2f get_offset() const;
    [[nodiscard]] float get_zoom() const;

    void set_follow_strategy(std::unique_ptr<FollowStrategy> follow_strategy);
    void set_offset(sf::Vector2f offset);
    void set_zoom(float zoom);

    void zoom_in();
    void zoom_out();

private:
    sf::Vector2f m_offset;
    float m_zoom_factor = 1.2f;
    float m_min_zoom_speed = .5f;
    float m_zoom_convergence_factor = 5.f;
    float m_current_zoom;
    float m_expected_zoom;
    std::unique_ptr<FollowStrategy> m_follow_strategy;
};

#endif
