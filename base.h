#pragma once

#include <iostream>
#include <string>
#include "glinc.h"
#include "errors.h"
#include "meshloader.h"

class BaseApp {
    public:
        BaseApp();
        BaseApp(unsigned int window_width, unsigned int window_height);
        ~BaseApp();

        int Initialize();
        void Run();
        
        GLFWwindow *window;
        unsigned int window_width;
        unsigned int window_height;
};
