#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 12.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    float zoom;
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 front, up, right;

    inline const void setNearPlane(float nearPlane) { pNearPlane = nearPlane; };
    inline const void setFarPlane(float farPlane) { pFarPlane = farPlane; };

    inline const float getNearPlane() const { return pNearPlane; };
    inline const float getFarPlane() const { return pFarPlane; };

    inline glm::mat4 getViewMatrix() const { return viewMatrix; };

    inline void lookAt(glm::vec3 target) { viewMatrix = glm::lookAt(position, target, up); }
    inline void setMovementSpeedMultiplier(float value = 1.0f) { movementSpeed = SPEED * value; };

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();
	glm::mat4 viewMatrix;
    glm::vec3 worldUp;
    float yaw, pitch, movementSpeed, mouseSensitivity;
    float pNearPlane, pFarPlane;
};

#endif // !CAMERA_H
