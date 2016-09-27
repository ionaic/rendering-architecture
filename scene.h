#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
    public:
        glm::vec4 position;
        glm::quat rotation;
        float scale;

        void Translate(glm::vec3 move);
        void Rotate(glm::vec3 axis, float angle);
        void Scale(float factor);

        glm::mat4 GetMatrix();

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

        Transform transform;
        Mesh mesh;
        Shader shader;

    protected:
        void SetModelMatrix();
};
