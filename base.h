#pragma once

#include <iostream>
#include <string>
#include "glinc.h"
#include "errors.h"
#include "scene.h"
#include "camera.h"

class BaseApp {
    public:
        BaseApp();
        BaseApp(unsigned int window_width, unsigned int window_height, std::string name);
        ~BaseApp();

        int Initialize();
        void Run();
        
        GLFWwindow *window;
        unsigned int window_width;
        unsigned int window_height;
        std::string window_name;

        SceneObject *scene;
        Camera *main_camera;
};
