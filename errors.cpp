#include "errors.h"

void checkGLError(const char *msg, const char *fname, const int line) {
    GLenum err = glGetError();

    if (err != GL_NO_ERROR) {
        std::cerr << std::string(fname) << ":" << line << " " << std::string(msg) << std::endl << "    ";
        switch (err) {
            case GL_INVALID_ENUM:
                std::cerr << "GL INVALID ENUM";
                break;
            case GL_INVALID_VALUE:
                std::cerr << "GL INVALID VALUE";
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "GL INVALID OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                std::cerr << "GL STACK OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                std::cerr << "GL STACK UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "GL OUT OF MEMORY";
                break;
            default:
                std::cerr << "GL UNKNOWN ERROR"; 
        }
        std::cerr << " " << err << " " << gluErrorString(err) << std::endl;
    }
#ifdef VERBOSE
    else {
        //output progress message even if no error
        errorMsg(msg, fname, line);
    }
#endif
}

void checkShader(GLuint shader, const char *fname) {
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

void checkProgram(const GLuint id, const GLuint fragment, const GLuint vertex) {
	glValidateProgram(id);
    checkGLError("Error validating shader program.", __FILE__, __LINE__);

	GLboolean isProgram = glIsProgram(id);
    std::cout << "    Program is " << (isProgram ? " " : "not ") << "a program" << std::endl;

	char buffer[2048];
	GLsizei length;
	glGetProgramInfoLog(id, 2048, &length, buffer);
    std::cout << "    Program Info Log (size " << length << "): " << buffer << std::endl;
	glGetShaderInfoLog(fragment, 2048, &length, buffer);
    std::cout << "    Fragment Shader Log (size " << length << "): " << buffer << std::endl;
	glGetShaderInfoLog(vertex, 2048, &length, buffer);
    std::cout << "    Vertex Shader Log (size " << length << "): " << buffer << std::endl;
}

void errorMsg(const char *msg, const char *fname, const int line) {
    std::cerr << fname << ":" << line << " " << msg << std::endl;
}
