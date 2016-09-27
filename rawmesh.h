#pragma once

#include <glm/glm.hpp>
#include <vector> 
#include <string>
#include <sstream>

class RawMesh {
    public: 
        RawMesh();
        ~RawMesh();

        // for adding the data to the mesh object
        void addPositions(const std::vector<glm::vec4> &poss);
        void addColors(const std::vector<glm::vec4> &cols);
        void addNormals(const std::vector<glm::vec3> &norms);
        void addUvs(const std::vector<glm::vec2> &uvs);
        void addUvs(const std::vector<glm::vec3> &uvs);
        void addIndexSet(const unsigned int positions, const unsigned int colors, const unsigned int normals, const unsigned int uvs);

        // for debugging/utility purposes
        std::string toString() const;

        // keeping Vertex/Face etc. definitions in the mesh class
        // this allows for different meshes to handle Vertices etc. differently
        // (mostly thinking about the extra info stored in the halfedge data structure)
        struct Vertex {
            glm::vec4 position;
            glm::vec4 color;
            glm::vec3 normal;
            glm::vec2 uv;
        };
        struct Triangle {
            unsigned int A;
            unsigned int B;
            unsigned int C;
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
};
