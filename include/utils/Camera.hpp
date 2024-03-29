#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <memory>
#include <SFML/Graphics.hpp>

struct Entity;
struct Camera;

struct FollowStrategy {
public:
    virtual void update(sf::Time delta_time) = 0;

    virtual ~FollowStrategy() = default;
};

struct SmoothFollowStrategy : FollowStrategy {
public:
    SmoothFollowStrategy(Camera *camera, std::shared_ptr<Entity> target);

    void update(sf::Time delta_time) override;

private:
    Camera *m_camera;
    std::shared_ptr<Entity> m_target;
    float m_min_speed = 0.5f;
    float m_convergence_factor = 3.f;
};

struct ControlledFollowStrategy : FollowStrategy {
public:
    explicit ControlledFollowStrategy(Camera *camera);

    void update(sf::Time delta_time) override;

private:
    Camera *m_camera;
    float m_move_speed = 10.f;
    float m_rotation_speed = 1.f;
};

struct Camera {
public:
    explicit Camera(std::nullptr_t);

    explicit Camera(sf::Vector2f offset, float zoom);

    void update(sf::Time delta_time);

    [[nodiscard]] sf::Vector2f get_offset() const;
    [[nodiscard]] float get_zoom() const;
    [[nodiscard]] float get_angle() const;

    void set_follow_strategy(std::unique_ptr<FollowStrategy> follow_strategy);
    void set_offset(sf::Vector2f offset);
    void set_zoom(float zoom);
    void set_angle(float angle);

    void zoom_in();
    void zoom_out();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    bool is_moving_left() const;
    bool is_moving_right() const;
    bool is_moving_up() const;
    bool is_moving_down() const;

private:
    sf::Vector2f m_offset = {0, 0};
    float m_angle{};
    float m_zoom_factor = 2.5f;
    float m_min_zoom_speed = .5f;
    float m_zoom_convergence_factor = 5.f;
    float m_current_zoom{};
    float m_expected_zoom{};
    std::unique_ptr<FollowStrategy> m_follow_strategy;
    float m_zooming = 1;

    bool m_is_moving_left = false;
    bool m_is_moving_right = false;
    bool m_is_moving_up = false;
    bool m_is_moving_down = false;
};

#endif // CAMERA_HPP_