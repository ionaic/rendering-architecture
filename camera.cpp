#include "camera.h"

glm::mat4 Camera::GetViewMatrix() {
    // return identity for the moment
    return glm::mat4(1.0f);
}

void Camera::Draw(const SceneObject *scene) {
    
}
