#include "mesh.h"

Mesh::Mesh() {
    std::cout << "CREATE MESH" << std::endl;
}
Mesh::~Mesh() {
    std::cout << "DESTRUCT MESH" << std::endl;
    glDeleteBuffers(1, &(this->buffers.vbo));
    glDeleteBuffers(1, &(this->buffers.ibo)) ;

    glDeleteVertexArrays(1, &(this->buffers.vao));
}

void Mesh::Initialize() {
    // generate the vao
    std::cout << "Pre init vao: " << this->buffers.vao << std::endl;
    glGenVertexArrays(1, &(this->buffers.vao));
    std::cout << "Post init vao: " << this->buffers.vao << std::endl;
    checkGLError("Generating VAO", __FILE__, __LINE__);

    // generate the vbos and ibo
    std::cout << "Pre init vbo: " << this->buffers.vbo << std::endl;
    glGenBuffers(1, &(this->buffers.vbo)) ;
    std::cout << "Post init vbo: " << this->buffers.vbo << std::endl;
    checkGLError("Generating VBO", __FILE__, __LINE__);
    std::cout << "Pre init ibo: " << this->buffers.ibo << std::endl;
    glGenBuffers(1, &(this->buffers.ibo)) ;
    std::cout << "Post init ibo: " << this->buffers.ibo << std::endl;
    checkGLError("Generating IBO", __FILE__, __LINE__);
}

void Mesh::SetupBuffers(Shader &shader) {
    glBindVertexArray(this->buffers.vao);
    checkGLError("Binding VAO", __FILE__, __LINE__);

    glEnableVertexAttribArray(this->buffers.vao);
    checkGLError("Enabling VAO", __FILE__, __LINE__);

    glEnableVertexArrayAttrib(this->buffers.vao, shader.position.location);
    checkGLError("Enabling attrib position", __FILE__, __LINE__);
    glEnableVertexArrayAttrib(this->buffers.vao, shader.color.location);
    checkGLError("Enabling attrib color", __FILE__, __LINE__);
    glEnableVertexArrayAttrib(this->buffers.vao, shader.normal.location);
    checkGLError("Enabling attrib normal", __FILE__, __LINE__);
    glEnableVertexArrayAttrib(this->buffers.vao, shader.uv.location);
    checkGLError("Enabling attrib uv", __FILE__, __LINE__);


    // enable the attributes
    //glEnableVertexAttribArray(shader.position.location);
    //glEnableVertexAttribArray(shader.color.location);
    //glEnableVertexAttribArray(shader.normal.location);
    //glEnableVertexAttribArray(shader.uv.location);
    checkGLError("Enabling vertex attributes.", __FILE__, __LINE__);

    // populate the buffer with data
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), (GLvoid*)&(this->vertices[0]), GL_STATIC_DRAW);

    // setup position vertex layout (float4 position)
    glVertexAttribPointer(shader.uv.location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&(this->vertices[0].position));
    // setup color vertex layout (float4 color)
    glVertexAttribPointer(shader.color.location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&(this->vertices[1].color));
    // setup normal vertex layout (float3 normal)
    glVertexAttribPointer(shader.normal.location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&(this->vertices[2].normal));
    // setup uv vertex layout (float2 uv)
    glVertexAttribPointer(shader.uv.location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&(this->vertices[3].uv));

    // setup the indexed draw
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * this->indices.size(), (GLvoid*)&(this->indices[0]), GL_STATIC_DRAW);

    Mesh::UseNone();

    // validating mesh
    bool meshOK = true;
    for (std::vector<Face>::iterator itr = this->indices.begin(); itr != this->indices.end(); ++itr) {
        if (itr->a >= this->vertices.size()) {
            std::cout << "Problem! " << itr->a << " >= " <<  this->vertices.size() << std::endl;
            meshOK = false;
        }
        if (itr->b >= this->vertices.size()) {
            std::cout << "Problem! " << itr->b << " >= " <<  this->vertices.size() << std::endl;
            meshOK = false;
        }
        if (itr->c >= this->vertices.size()) {
            std::cout << "Problem! " << itr->c << " >= " <<  this->vertices.size() << std::endl;
            meshOK = false;
        }
    }
    if (meshOK) {
        std::cout << "Mesh OK!" << std::endl;
    }
    else {
        std::cout << "Mesh indices have issues!" << std::endl;
    }
}

void Mesh::UseMesh() const {
    glBindVertexArray(this->buffers.vao);
    checkGLError("Binding VAO", __FILE__, __LINE__);

    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo);
    checkGLError("Binding VBO", __FILE__, __LINE__);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers.ibo);
    checkGLError("Binding VIO", __FILE__, __LINE__);
}

void Mesh::UseNone() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
