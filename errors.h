// NOTE: most of this is copied from past projects of mine

#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "glinc.h"
#include "shader.h"


// check for a gl error, 
void checkGLError(const char *msg, const char *fname, const int line);
struct ShaderInfo;
/*! */
void checkGLFramebufferError(const char *fname, const int line);
void checkGLReadFramebufferError(const char *fname, const int line);
void checkGLProgramError(ShaderInfo shdr, const char *fname, const int line);

// mostly copied from example for debugging purposes
//void checkShader(GLuint shader);
/*! Check the status of shader compilation. */
void checkShader(GLuint shader, const char *fname = NULL);

/*! Print an error message in the format file:line error.*/
void errorMsg(const char *msg, const char *fname, const int line);
/*! Check validity of shader program and grab logs for the program. */
void checkProgram(const GLuint id, const GLuint frag, const GLuint vert);

#else
#ifdef DEBUG
#warning Multiple definitions of __FILE__.
#endif
#endif
