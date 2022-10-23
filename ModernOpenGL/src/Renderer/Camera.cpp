#include "Renderer/Camera.h"

#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Log.h"

Camera::Camera()
    : m_Position(DEFAULT_POSITION),
    m_Front(DEFAULT_FRONT), m_Up(DEFAULT_UP), m_Right(DEFAULT_RIGHT),
    m_Yaw(DEFAULT_YAW), m_Pitch(DEFAULT_PITCH), m_Speed(DEFAULT_SPEED),
    m_MouseSensitivity(DEFAULT_MOUSE_SENSITIVITY), m_Zoom(DEFAULT_ZOOM) {
}

void Camera::onUpdate(float dt) {
    if (Input::isKeyPressed(Key::W))            _Move(CameraMovement::FORWARD, dt);
    if (Input::isKeyPressed(Key::S))            _Move(CameraMovement::BACKWARD, dt);
    if (Input::isKeyPressed(Key::A))            _Move(CameraMovement::LEFT, dt);
    if (Input::isKeyPressed(Key::D))            _Move(CameraMovement::RIGHT, dt);
    if (Input::isKeyPressed(Key::Space))        _Move(CameraMovement::UP, dt);
    if (Input::isKeyPressed(Key::LeftShift))    _Move(CameraMovement::DOWN, dt);

    bool CameraEnabled = Application::get().getWindow().isCursorDisabled();
    if (!CameraEnabled) {
        m_LastIsEnabled = CameraEnabled;
        return;
    }

    const glm::vec2 MousePos = Input::getMousePosition();
    const glm::vec2 MouseOffset = (m_LastIsEnabled ? MousePos - m_LastMousePos : glm::vec2(0.0f, 0.0f));
    m_LastIsEnabled = CameraEnabled;
    m_LastMousePos = MousePos;
    if (MouseOffset != glm::vec2(0.0f, 0.0f)) {
        m_Yaw += MouseOffset.x * dt * m_MouseSensitivity;
        m_Pitch -= MouseOffset.y * dt * m_MouseSensitivity;
        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);
        _UpdateDir();
    }
}

void Camera::_Move(CameraMovement dir, float dt) {
    glm::vec3 dir_v;

    switch (dir) {
    case CameraMovement::FORWARD:
        dir_v = m_Front;
        break;

    case CameraMovement::BACKWARD:
        dir_v = -m_Front;
        break;

    case CameraMovement::LEFT:
        dir_v = -m_Right;
        break;

    case CameraMovement::RIGHT:
        dir_v = m_Right;
        break;

    case CameraMovement::UP:
        dir_v = m_Up;
        break;

    case CameraMovement::DOWN:
        dir_v = -m_Up;
        break;

    default:
        dir_v = glm::vec3(0.0f, 0.0f, 0.0f);
        break;
    }

    m_Position += dir_v * m_Speed * dt;
}

void Camera::_UpdateDir() {
    glm::vec3 front(
        glm::cos(glm::radians(m_Pitch)) * glm::cos(glm::radians(m_Yaw)),
        glm::sin(glm::radians(m_Pitch)),
        glm::cos(glm::radians(m_Pitch)) * glm::sin(glm::radians(m_Yaw)));
    m_Front = glm::normalize(front);

    static const glm::vec3 worldup(0.0f, 1.0f, 0.0f);
    m_Right = glm::normalize(glm::cross(m_Front, worldup));
    m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
}
