#pragma once
#include <glm/glm.hpp>
#include "mesh.h"
#include "scene.h"

class Camera : public SceneObject {
    glm::mat4 GetViewMatrix();

    void Draw(const SceneObject *scene);
};
