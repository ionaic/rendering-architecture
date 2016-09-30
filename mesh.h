#pragma once
#include "camera.h"
#include "glinc.h"

// abstract mesh type
class Mesh {
    friend class Camera;
    public:
        Mesh();
        ~Mesh();

        void Initialize();
        virtual void SetBuffers() = 0;
    protected:
        struct BufferInfo {
            GLint vbo;
            GLint vao;
            GLint ibo;
        };
        
};
