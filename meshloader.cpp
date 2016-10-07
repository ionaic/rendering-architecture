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

void OBJMeshLoader::CombineIndices() {
    for (std::vector<std::vector<IndexSet> >::iterator idxs = multi_faces.begin(); idxs != multi_faces.end(); ++idxs) {
        // TODO currently ignoring when the face is non-triangular
        if (idxs->size() < 3) {
            continue;
        }

        Vertex a, b, c;
        a.position = this->vertex_positions[(*idxs)[0].position_idx];
        b.position = this->vertex_positions[(*idxs)[1].position_idx];
        c.position = this->vertex_positions[(*idxs)[2].position_idx];

        if ((*idxs)[0].normal_idx >= 0) {
            a.normal = this->vertex_normals[(*idxs)[0].normal_idx];
        }
        else {
            a.normal = glm::vec3(0);
        }
        if ((*idxs)[1].normal_idx >= 0) {
            b.normal = this->vertex_normals[(*idxs)[1].normal_idx];
        }
        else {
            b.normal = glm::vec3(0);
        }
        if ((*idxs)[2].normal_idx >= 0) {
            c.normal = this->vertex_normals[(*idxs)[2].normal_idx];
        }
        else {
            c.normal = glm::vec3(0);
        }

        if ((*idxs)[0].uv_idx >= 0) {
            a.uv = this->vertex_uvs[(*idxs)[0].uv_idx];
        }
        else {
            a.uv = glm::vec2(0);
        }
        if ((*idxs)[1].uv_idx >= 0) {
            b.uv = this->vertex_uvs[(*idxs)[1].uv_idx];
        }
        else {
            b.uv = glm::vec2(0);
        }
        if ((*idxs)[2].uv_idx >= 0) {
            c.uv = this->vertex_uvs[(*idxs)[2].uv_idx];
        }
        else {
            c.uv = glm::vec2(0);
        }

        a.color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        b.color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        c.color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

        this->vertices.push_back(a);
        this->vertices.push_back(b);
        this->vertices.push_back(c);
        
        Face out;
        out.a = this->vertices.size() - 3;
        out.b = this->vertices.size() - 2;
        out.c = this->vertices.size() - 1;

        this->faces.push_back(out);
    }
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
        else if (entry_type.compare("vt") == 0) {
            // TODO handles 2d textures only
            std::vector<float> tmp;
            float value;
            while (str >> value) {
                tmp.push_back(value);
            }
            if (tmp.size() > 1) {
                this->vertex_uvs.push_back(glm::vec2(tmp[0], tmp[1]));
            }
        }
        else if (entry_type.compare("f") == 0) {
            std::string tmp;
            std::vector<IndexSet> out;
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

                out.push_back(vert_out);
            }
            this->multi_faces.push_back(out);
        }
    }

    this->CombineIndices();

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
    std::cout << "Faces (" << this->multi_faces.size() << "): " << std::endl;
    for (unsigned int idx = 0; idx < this->multi_faces.size(); ++idx) {
        std::cout << "\t(";
        for (unsigned int idx2 = 0; idx2 < multi_faces[idx].size(); ++idx2) {
            std::cout << multi_faces[idx][idx2].position_idx << "/";
            std::cout << multi_faces[idx][idx2].uv_idx << "/";
            std::cout << multi_faces[idx][idx2].normal_idx << " ";
        }
        std::cout << ")" << std::endl;
    }
#endif
}

void OBJMeshLoader::CloseFile() {
    this->_file.close();
}

RawMesh* OBJMeshLoader::ParseToRawMesh(bool singlebuffer) const {
    RawMesh *out_mesh = new RawMesh();
    
    if (!singlebuffer) { 
        out_mesh->addPositions(this->vertex_positions);
        out_mesh->addNormals(this->vertex_normals);
        out_mesh->addUvs(this->vertex_uvs);
        out_mesh->addColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    }
    else {
        out_mesh->addVertices(this->vertices);
        out_mesh->addFaces(this->faces);
    }

    return out_mesh;
}
