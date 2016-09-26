#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <glm/glm.hpp>

#include "rawmesh.h"

// mesh factory
// TODO ideally would have made a meshloader abstract and this would be the
// concrete, but I didn't think ahead that far
class OBJMeshLoader {
    public:
        OBJMeshLoader();
        OBJMeshLoader(std::string filename);
        ~OBJMeshLoader();

        void OpenFile(std::string filename);
        void LoadLines();
        void CloseFile();
        RawMesh* ParseToRawMesh();
        //HalfEdge* ParseToHalfEdge();

    private:
        // file read
        std::string _filename;
        std::fstream _file;

        // intermediary mesh representation
        struct VertexIndices {
            unsigned int position_idx;
            unsigned int uv_idx;
            unsigned int normal_idx;
        };
        struct Face {
            std::deque<VertexIndices> vertex_indices;
        };
        std::deque<glm::vec4> vertex_positions;
        std::deque<glm::vec3> vertex_uvs;
        std::deque<glm::vec3> vertex_normals;
        // TODO ignoring parameter space coordinates for now
        // TODO Assuming triangular faces
        std::deque<Face> faces;
};
