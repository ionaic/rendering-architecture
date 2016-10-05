#include "rawmesh.h"

RawMesh::RawMesh() {

}

void RawMesh::addPositions(const std::vector<glm::vec4> &poss) {
    this->positions.insert(this->positions.end(), poss.begin(), poss.end());
}
void RawMesh::addColors(const std::vector<glm::vec4> &cols) {
    this->colors.insert(this->colors.end(), cols.begin(), cols.end());
}
void RawMesh::addNormals(const std::vector<glm::vec3> &norms) {
    this->normals.insert(this->normals.end(), norms.begin(), norms.end());
}
void RawMesh::addUvs(const std::vector<glm::vec2> &uvs) {
    this->uvs.insert(this->uvs.end(), uvs.begin(), uvs.end());
}
void RawMesh::addUvs(const std::vector<glm::vec3> &uvs) {
    for (std::vector<glm::vec3>::const_iterator itr = uvs.begin(); itr != uvs.end(); ++itr) {
        this->uvs.push_back(glm::vec2((*itr)[0], (*itr)[1]));
    }
}

void RawMesh::addPosition(const glm::vec4 &pos) {
    this->positions.push_back(pos);
}
void RawMesh::addColor(const glm::vec4 &col) {
    this->colors.push_back(col);
}
void RawMesh::addNormal(const glm::vec3 &norm) {
    this->normals.push_back(norm);
}
void RawMesh::addUv(const glm::vec2 &uv) {
    this->uvs.push_back(uv);
}
void RawMesh::addUv(const glm::vec3 &uv) {
    this->uvs.push_back(glm::vec2(uv[0], uv[1]));
}

void RawMesh::addIndexSet(const unsigned int position, const unsigned int color, const unsigned int normal, const unsigned int uv) {
    IndexSet tmp;
    tmp.position = position;
    tmp.color = color;
    tmp.normal = normal;
    tmp.uv = uv;
    indices.push_back(tmp);
}

std::string RawMesh::toString() const {
    std::stringstream out;

    out << "Position data: ";
    for (std::vector<glm::vec4>::const_iterator pos = this->positions.begin(); pos != this->positions.end(); ++pos) {
        out << "\n\t(" << (*pos)[0] << ", " << (*pos)[1] << ", " << (*pos)[2] << ", " << (*pos)[3] << ")";
    }

    out << std::endl << "Color data: ";
    for (std::vector<glm::vec4>::const_iterator col = this->colors.begin(); col != this->colors.end(); ++col) {
        out << "\n\t(" << (*col)[0] << ", " << (*col)[1] << ", " << (*col)[2] << ", " << (*col)[3] << ")";
    }

    out << std::endl << "Normal data: ";
    for (std::vector<glm::vec3>::const_iterator norm = this->normals.begin(); norm != this->normals.end(); ++norm) {
        out << "\n\t(" << (*norm)[0] << ", " << (*norm)[1] << ", " << (*norm)[2] << ")";
    }

    out << std::endl << "UV data: ";
    for (std::vector<glm::vec2>::const_iterator uv = this->uvs.begin(); uv != this->uvs.end(); ++uv) {
        out << "\n\t(" << (*uv)[0] << ", " << (*uv)[1] << ")";
    }

    return out.str();
}

