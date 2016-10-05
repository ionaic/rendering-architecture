#pragma once
#include "glinc.h"
#include "shader.h"
#include <vector>

class Camera;

struct Vertex { 
    glm::vec4 position;
    glm::vec4 color;
    glm::vec3 normal;
    glm::vec2 uv;
};
struct Face {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

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
        static const unsigned int bufferidx_position = 0;
        static const unsigned int bufferidx_color = 1;
        static const unsigned int bufferidx_normal = 2;
        static const unsigned int bufferidx_uv = 3;
        struct BufferInfo {
            GLuint vbo; // vbo for vertices
            GLuint vao; // vao (vertex attribute specifications)
            GLuint ibo; // index buffer for indexed draw
        };
        // for separate buffers for each
        //std::vector<glm::vec4> positions;
        //std::vector<glm::vec4> colors;
        //std::vector<glm::vec3> normals;
        //std::vector<glm::vec2> uvs;
        
        // for combined buffers
        std::vector<Vertex> vertices;

        // index information
        std::vector<Face> indices;

        // buffer ids
        BufferInfo buffers;
};
