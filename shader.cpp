#include "shader.h"

bool Shader::CheckShader(GLuint shader) {
    return Shader::CheckShader(shader, "");
}

bool Shader::CheckShader(GLuint shader, std::string fname) {
    GLint status, len;
    GLchar log[1024];

    // retrieve compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // get the log
    glGetShaderInfoLog(shader, sizeof(log), &len, log);

    std::string logstr(log);

    // print it out
    if (status) {
        std::cout << "OpenGL Shader Compile OK:\n" << logstr << std::endl;
        return true;
    }
    else {
        std::cerr << "GLSL Compilation Error in " << fname << ": " << std::endl << logstr << std::endl;
        return false;
    }
}
bool Shader::CheckProgram(const GLuint program, const GLuint fragment, const GLuint vertex) {
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
    return linkStatus && isProgram;
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

std::string Shader::VertexSource() {
    return this->vertex_src;
}
void Shader::VertexSource(std::string src) {
    std::cout << "Vertex source: " << std::endl << src << std::endl << "----------------------" << std::endl;
    this->vertex_src = src;
}

std::string Shader::FragmentSource() {
    return this->fragment_src;
}
void Shader::FragmentSource(std::string src) {
    std::cout << "Fragment source: " << std::endl << src << std::endl << "----------------------" << std::endl;
    this->fragment_src = src;
}

void Shader::ReadVertexFromFile(std::string fname) {
    this->VertexSource(this->ReadFile(fname));
}

void Shader::ReadFragmentFromFile(std::string fname) {
    this->FragmentSource(this->ReadFile(fname));
}

std::string Shader::ReadFile(std::string fname) {
    std::ifstream file(fname, std::ios_base::in);
    std::string src;

    file.seekg(0, std::ios::end);
    src.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    src.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return src;
}

bool Shader::Initialize(bool print_log) {
    int src_len = 0;
    bool err = false;

    // set up vertex shader
    this->vertex = glCreateShader(GL_VERTEX_SHADER);
    checkGLError("Creating vertex shader", __FILE__, __LINE__);
    src_len = this->vertex_src.size();
    const GLchar *vsrc = this->vertex_src.c_str();
    glShaderSource(this->vertex, 1, &vsrc, &src_len);
    checkGLError("Setting vertex shader source", __FILE__, __LINE__);
    glCompileShader(this->vertex);
    checkGLError("Compiling vertex shader", __FILE__, __LINE__);
    err = err || Shader::CheckShader(this->vertex);

    // set up fragment shader
    this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    checkGLError("Creating fragment shader", __FILE__, __LINE__);
    src_len = this->fragment_src.size();
    const GLchar *fsrc = this->fragment_src.c_str();
    glShaderSource(this->fragment, 1, &fsrc, &src_len);
    checkGLError("Setting fragment shader source", __FILE__, __LINE__);
    glCompileShader(this->fragment);
    checkGLError("Compiling fragment shader", __FILE__, __LINE__);
    err = err || Shader::CheckShader(this->fragment);

    this->program = glCreateProgram();
    checkGLError("Creating shader program", __FILE__, __LINE__);
    glAttachShader(this->program, this->vertex);
    checkGLError("Attaching vertex shader", __FILE__, __LINE__);
    glAttachShader(this->program, this->fragment);
    checkGLError("Attaching fragment shader", __FILE__, __LINE__);

    glLinkProgram(this->program);
    checkGLError("Linking shader program", __FILE__, __LINE__);
    err = err || Shader::CheckProgram(this->program, this->fragment, this->vertex);

    // if the program failed to initialize this will segfault
    if (!err) {
        this->position.FindInShader(this->program);
        this->color.FindInShader(this->program);
        this->normal.FindInShader(this->program);
        this->uv.FindInShader(this->program);
    }
    
    return err;
}

void Shader::UseShader() const {
    glUseProgram(this->program);
}

void Shader::AddAttribute(std::string name) {
    VertexAttribute attr;
    attr.name = name;
    attr.FindInShader(this->vertex);
    this->attributes.push_back(attr);
}

void VertexAttribute::FindInShader(GLuint shader) {
    this->location = glGetAttribLocation(shader, this->name.c_str());
    std::string msg = "Getting attribute location " + this->name;
    checkGLError(msg.c_str(), __FILE__, __LINE__);
}

void VertexAttribute::BindLocation(GLuint program) {
    glBindAttribLocation(program, location, name.c_str());
}
