#include "meshloader.h"

// default constructor
OBJMeshLoader::OBJMeshLoader() {

}
OBJMeshLoader::~OBJMeshLoader() {

}

void OBJMeshLoader::OpenFile(std::string filename) {
    this->_filename = filename;
    // open file for reading
    this->_file.open(this->_filename.c_str());
}

void OBJMeshLoader::LoadLines() {
    std::string line;
    
    while (std::getline(this->_file, line)) {
        std::stringstream str(line);

        std::string entry_type;
        str >> entry_type;
        if (entry_type.compare("v") == 0) {
            std::vector<float> tmp;
            float value;
            while (str >> value) {
                tmp.push_back(value);
            }
            if (tmp.size() > 3) {
                this->vertex_positions.push_back(glm::vec4(tmp[0], tmp[1], tmp[2], tmp[3]));
            }
            else if (tmp.size() == 3) {
                this->vertex_positions.push_back(glm::vec4(tmp[0], tmp[1], tmp[2], 1.0f));
            }
        }
        else if (entry_type.compare("vn") == 0) {
            std::vector<float> tmp;
            float value;
            while (str >> value) {
                tmp.push_back(value);
            }
            if (tmp.size() > 2) {
                this->vertex_normals.push_back(glm::vec3(tmp[0], tmp[1], tmp[2]));
            }
        }
        else if (entry_type.compare("f") == 0) {
            std::string tmp;
            Face out;
            while (str >> tmp) {
                std::stringstream line_str(tmp);
                std::string tmp_pos;
                std::string tmp_uv;
                std::string tmp_norm;

                IndexSet vert_out;
                std::getline(line_str, tmp_pos, '/');
                std::getline(line_str, tmp_uv, '/');
                std::getline(line_str, tmp_norm);

                std::stringstream conv_str;

                conv_str << " " << tmp_pos;
                conv_str >> vert_out.position_idx;

                if (tmp_uv.size() > 0) {
                    conv_str.clear();
                    conv_str << " " << tmp_uv;
                    conv_str >> vert_out.uv_idx;
                }
                else {
                    vert_out.uv_idx = -1;
                }

                if (tmp_norm.size() > 0) {
                    conv_str.clear();
                    conv_str << " " << tmp_norm;
                    conv_str >> vert_out.normal_idx;
                }
                else {
                    vert_out.normal_idx = -1;
                }

                out.indices.push_back(vert_out);
            }
            this->faces.push_back(out);
        }
    }

#ifdef DEBUG
    // debugging print statements
    std::cout << "Vertex positions (" << this->vertex_positions.size() << "): " << std::endl;
    for (unsigned int idx = 0; idx < this->vertex_positions.size(); ++idx) {
        std::cout << "\t(" << vertex_positions[idx][0] << ", " << vertex_positions[idx][1] << ", " << vertex_positions[idx][2] << ", " << vertex_positions[idx][3] << ")" << std::endl;
    }
    std::cout << "Vertex normals (" << this->vertex_normals.size() << "): " << std::endl;
    for (unsigned int idx = 0; idx < this->vertex_normals.size(); ++idx) {
        std::cout << "\t(" << vertex_normals[idx][0] << ", " << vertex_normals[idx][1] << ", " << vertex_normals[idx][2] << " )" << std::endl;
    }
    std::cout << "Faces (" << this->faces.size() << "): " << std::endl;
    for (unsigned int idx = 0; idx < this->faces.size(); ++idx) {
        std::cout << "\t(";
        for (unsigned int idx2 = 0; idx2 < faces[idx].indices.size(); ++idx2) {
            std::cout << faces[idx].indices[idx2].position_idx << "/";
            std::cout << faces[idx].indices[idx2].uv_idx << "/";
            std::cout << faces[idx].indices[idx2].normal_idx << " ";
        }
        std::cout << ")" << std::endl;
    }
#endif
}

void OBJMeshLoader::CloseFile() {
    this->_file.close();
}

RawMesh* OBJMeshLoader::ParseToRawMesh() const {
    RawMesh *out_mesh = new RawMesh();
    
    out_mesh->addPositions(this->vertex_positions);
    out_mesh->addNormals(this->vertex_normals);
    out_mesh->addUvs(this->vertex_uvs);
    out_mesh->colors.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

    for (std::vector<Face>::const_iterator face_itr = faces.begin(); face_itr != faces.end(); ++face_itr) {
        for (std::vector<IndexSet>::const_iterator idx_itr = face_itr->indices.begin(); idx_itr != face_itr->indices.end(); ++idx_itr) {
            out_mesh->addIndexSet(idx_itr->position_idx, 0, idx_itr->normal_idx, idx_itr->uv_idx);
        }
    }

    return out_mesh;
}
