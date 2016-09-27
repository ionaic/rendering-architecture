#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
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
        RawMesh* ParseToRawMesh() const;
        //HalfEdge* ParseToHalfEdge();

    private:
        // file read
        std::string _filename;
        std::ifstream _file;

        // intermediary mesh representation
        struct IndexSet {
            unsigned int position_idx;
            int uv_idx;
            int normal_idx;
        };
        struct Face {
            std::vector<IndexSet> indices;
        };
        std::vector<glm::vec4> vertex_positions;
        std::vector<glm::vec3> vertex_uvs;
        std::vector<glm::vec3> vertex_normals;
        // TODO ignoring parameter space coordinates for now
        // TODO Assuming triangular faces
        std::vector<Face> faces;
        // TODO ignoring groups and shading instructions
};
