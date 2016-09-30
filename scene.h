#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iterator>

#include "mesh.h"
#include "shader.h"

class Mesh;

class Transform {
    public:
        glm::vec4 position;
        glm::quat rotation;
        glm::vec3 scale;

        Transform();
        ~Transform();

        void Translate(float x, float y, float z);
        void Translate(glm::vec3 move);
        void Rotate(glm::vec3 axis, float angle);
        void Scale(float x, float y, float z);
        void Scale(glm::vec3 factors);

        glm::mat4 GetMatrix() const;

    private:
        struct VectorBasis {
            glm::vec4 up;
            glm::vec4 left;
            glm::vec4 forward;
        };
        VectorBasis basis;
};

class SceneObject {
    public:
        SceneObject();
        ~SceneObject();

        Transform transform;
        Mesh *mesh;
        Shader shader;

    protected:
        void SetModelMatrix();
};
