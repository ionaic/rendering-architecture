#pragma once

#include <iostream>
#include <string>
#include "glinc.h"
#include "shader.h"


// check for a gl error, 
void checkGLError(const char *msg, const char *fname, const int line);
struct ShaderInfo;
// Check the status of shader compilation.
void checkShader(GLuint shader, const char *fname = NULL);

// Check validity of shader program and grab logs for the program.
void checkProgram(const GLuint id, const GLuint frag, const GLuint vert);
// Print an error message in the format file:line error.
void errorMsg(const char *msg, const char *fname, const int line);
