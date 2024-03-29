#include "utils/Camera.hpp"
#include "game_objects/bodies/Body.hpp"
#include "game_objects/entities/Entity.hpp"
#include "logic/World.hpp"

SmoothFollowStrategy::SmoothFollowStrategy(
    Camera *camera,
    std::shared_ptr<Entity> target
)
    : m_camera(camera), m_target(std::move(target)) {
}

void SmoothFollowStrategy::update(sf::Time delta_time) {
    if (!m_target) {
        return;
    }
    sf::Vector2f delta_target =
        m_target->get_body().get_position() - m_camera->get_offset();
    float length = sqrtf(powf(delta_target.x, 2) + powf(delta_target.y, 2));
    sf::Vector2f delta_move = delta_target * m_convergence_factor;
    float speed = sqrtf(powf(delta_move.x, 2) + powf(delta_move.y, 2));
    if (speed == 0) {
        return;
    }
    float target_distance =
        sqrtf(powf(delta_target.x, 2) + powf(delta_target.y, 2));
    if (speed < m_min_speed) {
        delta_move *= m_min_speed / speed;
        speed = m_min_speed;
    }
    if (speed * delta_time.asSeconds() > target_distance) {
        delta_move *= target_distance / speed;
    }
    m_camera->set_offset(
        m_camera->get_offset() + delta_move * delta_time.asSeconds()
    );
    sf::Vector2f delta_target2 =
        m_target->get_body().get_position() - m_camera->get_offset();
    float length2 = sqrtf(powf(delta_target2.x, 2) + powf(delta_target2.y, 2));
    float delta_angle =
        m_target->getRotation() / (180.f / M_PIf) - m_camera->get_angle();
    delta_angle -= floor(delta_angle / M_PIf) * M_PIf;
    if (delta_angle > M_PI_2f) {
        delta_angle = M_PIf - delta_angle;
    }
    float delta_rotation = delta_angle / length * length2;
    m_camera->set_angle(
        m_target->getRotation() / (180.f / M_PIf) - delta_rotation
    );
}

Camera::Camera(std::nullptr_t) {}

Camera::Camera(sf::Vector2f offset, float zoom)
    : m_offset(offset), m_current_zoom(zoom), m_expected_zoom(zoom) {}

void Camera::update(sf::Time delta_time) {
    if (m_follow_strategy) {
        m_follow_strategy->update(delta_time);
    }
    m_expected_zoom *= powf(m_zooming, delta_time.asSeconds());
    float delta_zoom = m_expected_zoom - m_current_zoom;
    float zoom_speed = delta_zoom * m_zoom_convergence_factor;
    if (zoom_speed < 0) {
        zoom_speed = std::min(zoom_speed, -m_min_zoom_speed);
    } else {
        zoom_speed = std::max(zoom_speed, m_min_zoom_speed);
    }
    float final_delta = zoom_speed * delta_time.asSeconds();
    if (abs(final_delta) > abs(delta_zoom)) {
        final_delta = delta_zoom;
    }
    m_current_zoom += final_delta;
    m_zooming = 1;
    m_is_moving_left = false;
    m_is_moving_right = false;
    m_is_moving_up = false;
    m_is_moving_down = false;
}

sf::Vector2f Camera::get_offset() const {
    return m_offset;
}

float Camera::get_zoom() const {
    return m_current_zoom;
}

void Camera::set_follow_strategy(std::unique_ptr<FollowStrategy> follow_strategy
) {
    m_follow_strategy = std::move(follow_strategy);
}

void Camera::set_offset(sf::Vector2f offset) {
    m_offset = offset;
}

void Camera::set_zoom(float zoom) {
    m_current_zoom = zoom;
    m_expected_zoom = zoom;
}

void Camera::zoom_in() {
    m_zooming = 1 / m_zoom_factor;
}

void Camera::zoom_out() {
    m_zooming = m_zoom_factor;
}

float Camera::get_angle() const {
    return m_angle;
}

void Camera::set_angle(float angle) {
    m_angle = angle;
}

void Camera::move_left() {
    m_is_moving_left = true;
}

void Camera::move_right() {
    m_is_moving_right = true;
}

void Camera::move_up() {
    m_is_moving_up = true;
}

void Camera::move_down() {
    m_is_moving_down = true;
}

bool Camera::is_moving_left() const {
    return m_is_moving_left;
}

bool Camera::is_moving_right() const {
    return m_is_moving_right;
}

bool Camera::is_moving_up() const {
    return m_is_moving_up;
}

bool Camera::is_moving_down() const {
    return m_is_moving_down;
}

ControlledFollowStrategy::ControlledFollowStrategy(Camera *camera)
    : m_camera(camera) {
}

void ControlledFollowStrategy::update(sf::Time delta_time) {
    float x_speed = 0;
    float y_speed = 0;
    float angle = atan2(m_camera->get_offset().y, m_camera->get_offset().x);
    if (m_camera->is_moving_left()) {
        angle -= m_rotation_speed * delta_time.asSeconds();
    }
    if (m_camera->is_moving_right()) {
        angle += m_rotation_speed * delta_time.asSeconds();
    }
    m_camera->set_angle(angle + M_PI_2f);
    float dist = sqrtf(
        powf(m_camera->get_offset().x, 2) + powf(m_camera->get_offset().y, 2)
    );
    m_camera->set_offset(sf::Vector2f(cos(angle), sin(angle)) * dist);
    if (m_camera->is_moving_up()) {
        x_speed += cos(angle);
        y_speed += sin(angle);
    }
    if (m_camera->is_moving_down()) {
        x_speed -= cos(angle);
        y_speed -= sin(angle);
    }
    x_speed *= m_move_speed * delta_time.asSeconds() * m_camera->get_zoom();
    y_speed *= m_move_speed * delta_time.asSeconds() * m_camera->get_zoom();
    m_camera->set_offset(
        m_camera->get_offset() + sf::Vector2f(x_speed, y_speed)
    );
}
