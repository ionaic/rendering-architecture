#pragma once
#include "glinc.h"
#include "shader.h"
#include <vector>

class Camera;

// base mesh type
// provides handling for the buffers, subtypes handle populating the data
class Mesh {
    friend class Camera;
    public:
        Mesh();
        ~Mesh();

        void Initialize();
        // setup the buffers for a shader
        void SetupBuffers(Shader &shader);
    protected:
        enum BufferIndices {
            position = 0,
            color = 1,
            normal = 2,
            uv = 3
        };
        struct BufferInfo {
            GLint vbo[4]; // vbos for position, color, normal, uv
            GLint vao; // vao (vertex attribute specifications)
            GLint ibo; // index buffer for indexed draw
        };
        struct IndexSet {
            unsigned int position;
            unsigned int color;
            unsigned int normal;
            unsigned int uv;
        };
        std::vector<glm::vec4> positions;
        std::vector<glm::vec4> colors;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        
        std::vector<IndexSet> indices;
        BufferInfo buffers;
};
