#pragma once

#include <glm/glm.hpp>
#include <vector> 
#include <string>
#include <sstream>
#include "mesh.h"

class RawMesh : public Mesh {
//class RawMesh {
    public: 
        RawMesh();
        ~RawMesh();

        // for adding the data to the mesh object
        void addPositions(const std::vector<glm::vec4> &poss);
        void addColors(const std::vector<glm::vec4> &cols);
        void addNormals(const std::vector<glm::vec3> &norms);
        void addUvs(const std::vector<glm::vec2> &uvs);
        void addUvs(const std::vector<glm::vec3> &uvs);

        void addPosition(const glm::vec4 &pos);
        void addColor(const glm::vec4 &col);
        void addNormal(const glm::vec3 &norm);
        void addUv(const glm::vec2 &uv);
        void addUv(const glm::vec3 &uv);

        void addVertex(const Vertex &v);
        void addVertices(const std::vector<Vertex> &vertices);
        void addFace(const unsigned int &a, const unsigned int &b, const unsigned int &c);
        void addFace(const Face &f);
        void addFaces(const std::vector<Face> &faces);

        // for debugging/utility purposes
        std::string toString() const;

        // keeping Vertex/Face etc. definitions in the mesh class
        // this allows for different meshes to handle Vertices etc. differently
        // (mostly thinking about the extra info stored in the halfedge data structure)
};
