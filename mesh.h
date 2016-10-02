#pragma once
#include "glinc.h"

class Camera;

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
