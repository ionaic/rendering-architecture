#pragma once
#include <glm/glm.hpp>
#include "scene.h"
#include "mesh.h"

class Camera : public SceneObject {
    glm::mat4 GetViewMatrix();

    void Draw(const SceneObject *scene);
};
