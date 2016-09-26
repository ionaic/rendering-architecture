#include <string>
#include "glinc.h"

struct ShaderInfo {
    GLint program;
    GLint vertex;
    GLint fragment;
    std::string vertex_name;
    std::string fragment_name;
};
