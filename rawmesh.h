#pragma once

#include <glm/glm.hpp>
#include <vector> 

class RawMesh {
    public: 
        struct Vertex {
            glm::vec4 position;
            glm::vec4 color;
            glm::vec3 normal;
            glm::vec2 uv;
        };
        
        std::vector<Vertex> vertices;
};
