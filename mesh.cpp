#include "mesh.h"

Mesh::Mesh() {}
Mesh::~Mesh() {
    glDeleteBuffers(4, &(this->buffers.vbo));
    glDeleteBuffers(1, &(this->buffers.ibo)) ;

    glDeleteVertexArrays(1, &(this->buffers.vao));
}

void Mesh::Initialize() {
    // generate the vbos and ibo
    glGenBuffers(4, &(this->buffers.vbo[0])) ;
    glGenBuffers(1, &(this->buffers.ibo)) ;

    // generate the vao
    glGenVertexArrays(1, &(this->buffers.vao));
}

void Mesh::SetupBuffers(Shader &shader) {
    glBindVertexArray(this->buffers.vao);

    // setup position vertex layout (float4 position)
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo[BufferIndices.position]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 4 * this->positions.size(), (GLvoid*)&(this->positions[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(shader.position.location, 4, GL_FLOAT, GL_FALSE, 0, 0);
    // setup color vertex layout (float4 color)
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo[BufferIndices.color]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 4 * this->colors.size(), (GLvoid*)&(this->colors[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(shader.color.location, 4, GL_FLOAT, GL_FALSE, 0, 0);
    // setup normal vertex layout (float3 normal)
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo[BufferIndices.normal]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 3 * this->normals.size(), (GLvoid*)&(this->normals[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(shader.normal.location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // setup uv vertex layout (float2 uv)
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers.vbo[BufferIndices.uv]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 2 * this->uvs.size(), (GLvoid*)&(this->uvs[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(shader.uv.location, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // setup the indexed draw
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 4 * this->indices.size(), (GLvoid*)&(this->indices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
