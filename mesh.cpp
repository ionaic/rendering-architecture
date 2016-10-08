#include "mesh.h"

Mesh::Mesh() {}
Mesh::~Mesh() {
    glDeleteBuffers(1, &(this->buffers.vbo));
    glDeleteBuffers(1, &(this->buffers.ibo)) ;

    glDeleteVertexArrays(1, &(this->buffers.vao));
}

void Mesh::Initialize() {
    // generate the vbos and ibo
    glGenBuffers(1, &(this->buffers.vbo)) ;
    glGenBuffers(1, &(this->buffers.ibo)) ;

    // generate the vao
    glGenVertexArrays(1, &(this->buffers.vao));
}

void Mesh::SetupBuffers(Shader &shader) {
    glBindVertexArray(this->buffers.vao);
    checkGLError("Binding VAO", __FILE__, __LINE__);

    // enable the attributes
    //glEnableVertexArrayAttrib(this->buffers.vao, shader.position.location);
    //glEnableVertexArrayAttrib(this->buffers.vao, shader.color.location);
    //glEnableVertexArrayAttrib(this->buffers.vao, shader.normal.location);
    //glEnableVertexArrayAttrib(this->buffers.vao, shader.uv.location);
    glEnableVertexAttribArray(shader.position.location);
    glEnableVertexAttribArray(shader.color.location);
    glEnableVertexAttribArray(shader.normal.location);
    glEnableVertexAttribArray(shader.uv.location);
    checkGLError("Enabling vertex attributes.", __FILE__, __LINE__);

    // populate the buffer with data
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), (GLvoid*)&(this->vertices[0]), GL_STATIC_DRAW);

    // setup position vertex layout (float4 position)
    glVertexAttribPointer(shader.uv.location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(this->vertices[0].position));
    // setup color vertex layout (float4 color)
    glVertexAttribPointer(shader.color.location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&(this->vertices[1].color));
    // setup normal vertex layout (float3 normal)
    glVertexAttribPointer(shader.normal.location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&(this->vertices[2].normal));
    // setup uv vertex layout (float2 uv)
    glVertexAttribPointer(shader.uv.location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&(this->vertices[3].uv));

    // setup the indexed draw
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 4 * this->indices.size(), (GLvoid*)&(this->indices[0]), GL_STATIC_DRAW);

    Mesh::UseNone();
}

void Mesh::UseMesh() const {
    //glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers.ibo);

    glBindVertexArray(this->buffers.vao);
}

void Mesh::UseNone() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
