#pragma once

#include <iostream>
#include <string>
#include "glinc.h"
#include "shader.h"


// check for a gl error, 
void checkGLError(const char *msg, const char *fname, const int line);

// Print an error message in the format file:line error.
void errorMsg(const char *msg, const char *fname, const int line);
