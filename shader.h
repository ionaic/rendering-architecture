#pragma once

#include <string>
#include <fstream>
#include <list>
#include "glinc.h"
#include "errors.h"

class VertexAttribute {
    public:
        GLuint location;
        std::string name;

        void FindInShader(GLuint shader);
        void BindLocation(GLuint program);
};

class ShaderUniform {
    public:
        GLuint location;
        std::string name;
};

class Shader {
    public:
        static void CheckShader(GLuint shader, char *fname = NULL);
        static void CheckProgram(const GLuint program, const GLuint fragment, const GLuint vertex);

        Shader();
        ~Shader();

        std::string VertexSource();
        void VertexSource(std::string src);
        std::string FragmentSource();
        void FragmentSource(std::string src);
        void ReadVertexFromFile(std::string fname);
        void ReadFragmentFromFile(std::string fname);
        void Initialize(bool print_log = true);
        void UseShader();
        void AddAttribute(std::string name);

        // TODO geometry, tesselation ctrl, tesselation eval
        GLuint program;
        GLuint vertex;
        GLuint fragment;

        // MVP is separate as it's needed by everything
        ShaderUniform model, view, projection;
        // position, normal, color, uv separate as they're needed most places
        VertexAttribute position, color, normal, uv;

        // storing the shader's vertex attributes and uniforms
        std::list<VertexAttribute> attributes;
        std::list<ShaderUniform> uniforms;
        
        // TODO ignoring textures for the moment
        // would want to package this into a Material class that tracks textures and
        // multiple shader passes

    private:
        std::string ReadFile(std::string fname);
        std::string vertex_src;
        std::string fragment_src;
};
