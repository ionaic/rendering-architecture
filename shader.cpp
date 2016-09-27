#include "shader.h"

static void Shader::CheckShader(GLuint shader, char *fname) {
    GLint status, len;
    GLchar log[1024];

    // retrieve compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // get the log
    glGetShaderInfoLog(shader, sizeof(log), &len, log);

    // print it out
    if (status) {
        std::cout << "OpenGL Shader Compile OK:\n" << log << std::endl;
    }
    else {
        std::cerr << "GLSL Compilation Error in " << std::string(fname) << ": " << std::endl << std::string(log) << std::endl;
    }
}
static void Shader::CheckProgram(const GLuint program, const GLuint frag, const GLuint vert) {
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    glValidateProgram(program);
    checkGLError("Error validating shader program.", __FILE__, __LINE__);

    GLboolean isProgram = glIsProgram(program);
    std::cout << "\tProgram is " << (isProgram ? " " : "not ") << "a program" << std::endl;

    char buffer[2048];
    GLsizei length;

    if (linkStatus == GL_TRUE) {
        std::cout << "OpenGL Program Link OK" << std::endl;
    }
    else {
        std::cerr << "OpenGL Link Error" << std::endl;
    }

    glGetProgramInfoLog(program, 2048, &length, buffer);
    std::cout << "\tProgram Info Log (size " << length << "): " << buffer << std::endl;
    glGetShaderInfoLog(fragment, 2048, &length, buffer);
    std::cout << "\tFragment Shader Log (size " << length << "): " << buffer << std::endl;
    glGetShaderInfoLog(vertex, 2048, &length, buffer);
    std::cout << "\tVertex Shader Log (size " << length << "): " << buffer << std::endl;
}

Shader::Shader() {
    this->model.name = "model";
    this->view.name = "view";
    this->projection.name = "projection";

    this->position.name = "position";
    this->color.name = "color";
    this->normal.name = "normal";
    this->uv.name = "uv";
}
Shader::~Shader() {
    // detach the shaders from the program
    glDetachShader(this->program, this->vertex);
    glDetachShader(this->program, this->fragment);
    
    // delete the shaders
    glDeleteShader(this->vertex);
    glDeleteShader(this->fragment);

    // delete the shader program
    glDeleteProgram(this->program);
    checkGLError("Destroying shader", __FILE__, __LINE__);
}

void Shader::VertexSource(std::string src) {
    this->vertex_src = src;
}

void Shader::FragmentSource(std::string src) {
    this->fragment_src = src;
}

void ReadVertexFromFile(std::string fname) {
    this->ReadFile(fname, 0x00);
}

void ReadFragmentFromFile(std::string fname) {
    this->ReadFile(fname, 0x01);
}

void Shader::ReadFile(std::string fname, char target) {
    std::ifstream file(fname, std::ios_base::in);

    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    char *buff = new char[length];
    file.read(buff, length);

    std::string src(buff);

    delete [] buff;

    if (target == 0x00) {
        // vertex shader
        this->VertexSource(src);
    }
    else if (target == 0x01) {
        // fragment shader
        this->FragmentSource(src);
    }
}

void Shader::Initialize(bool print_log) {
    // set up vertex shader
    this->vertex = glCreateShader(GL_VERTEX_SHADER);
    checkGLError("Creating vertex shader", __FILE__, __LINE__);
    glShaderSource(this->vertex);
    checkGLError("Setting vertex shader source", __FILE__, __LINE__);
    glCompileShader(this->vertex);
    checkGLError("Compiling vertex shader", __FILE__, __LINE__);
    Shader::CheckShader(this->vertex);

    // set up fragment shader
    this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    checkGLError("Creating fragment shader", __FILE__, __LINE__);
    glShaderSource(this->fragment);
    checkGLError("Setting fragment shader source", __FILE__, __LINE__);
    glCompileShader(this->fragment);
    checkGLError("Compiling fragment shader", __FILE__, __LINE__);
    Shader::CheckShader(this->fragment);

    this->program = glCreateProgram();
    checkGLError("Creating shader program", __FILE__, __LINE__);
    glAttachShader(this->program, this->vertex);
    checkGLError("Attaching vertex shader", __FILE__, __LINE__);
    glAttachShader(this->program, this->fragment);
    checkGLError("Attaching fragment shader", __FILE__, __LINE__);

    glLinkProgram(this->program);
    checkGLError("Linking shader program", __FILE__, __LINE__);
    Shader::CheckProgram(this->program, this->fragment, this->vertex);
}

void Shader::UseShader() {
    glUseProgram(this->program);
}

void Shader::AddAttribute(std::string name) {
    VertexAttribute attr;
    attr.name = name;
    attr.FindInShader(this->shader);
    this->attributes.push_back(attr);
}

void VertexAttribute::FindInShader(GLuint shader) {
    this->location = glGetAttribLocation(shader, this->name.c_str());
    checkGLError("Getting attribute location", __FILE__, __LINE__);
}

void VertexAttribute::BindLocation(GLuint program) {
    glBindAttributeLocation(program, location, name);
}
