#pragma once
#include <glm/glm.hpp>

class Camera : SceneObject {
    glm::mat4 GetViewMatrix();

    void Draw(const SceneObject *scene);
};
