#include "meshloader.h"

// default constructor
OBJMeshLoader::OBJMeshLoader() {
    
}

OBJMeshLoader::OBJMeshLoader(std::string filename) {
    this->OpenFile(this->_filename);
}
OBJMeshLoader::~OBJMeshLoader() {

}

void OBJMeshLoader::OpenFile(std::string filename) {
    this->_filename = filename;
    // open file for reading
    this->_file.open(this->_filename.c_str(), std::ios_base::in);

}

void OBJMeshLoader::LoadLines() {
    std::string line;
    
    while (this->_file >> line) {
        std::cout << "Read line: " << line << std::endl;
    }
}

void OBJMeshLoader::CloseFile() {
    this->_file.close();
}

RawMesh* OBJMeshLoader::ParseToRawMesh() {
    RawMesh *out_mesh = new RawMesh();

    return out_mesh;
}
