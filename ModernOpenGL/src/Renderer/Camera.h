#ifndef RENDERER_CAMERA_H_
#define RENDERER_CAMERA_H_

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement {
    NONE = 0, FORWARD, BACKWARD, LEFT, RIGHT,
};

class Camera {
public:
    Camera();
    //Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);
    
    inline glm::mat4 getViewMatrix() {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    void onUpdate(float dt);

private:
    void _Move(CameraMovement dir, float dt);
    void _UpdateDir();

private:
    static inline const glm::vec3 DEFAULT_POSITION      = glm::vec3(0.0f, 0.0f,  3.0f);
    static inline const glm::vec3 DEFAULT_FRONT         = glm::vec3(0.0f, 0.0f, -1.0f);
    static inline const glm::vec3 DEFAULT_UP            = glm::vec3(0.0f, 1.0f,  0.0f);
    static inline const glm::vec3 DEFAULT_RIGHT         = glm::vec3(1.0f, 0.0f,  0.0f);
    static constexpr float DEFAULT_YAW                  = -90.0f;
    static constexpr float DEFAULT_PITCH                = 0.0f;
    static constexpr float DEFAULT_SPEED                = 5.0f;
    static constexpr float DEFAULT_MOUSE_SENSITIVITY    = 2.0f;
    static constexpr float DEFAULT_ZOOM                 = 45.0f;

private:
    glm::vec3 m_Position, m_Front, m_Up, m_Right;
    float m_Yaw, m_Pitch, m_Speed, m_MouseSensitivity, m_Zoom;
    glm::vec2 m_LastMousePos = glm::vec2(0.0f, 0.0f);
    bool m_LastIsEnabled = false;
};

#endif // !RENDERER_CAMERA_H_