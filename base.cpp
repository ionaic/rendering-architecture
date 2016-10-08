#include "base.h"

BaseApp::BaseApp() {
    BaseApp(640, 480, "Teapot Explosion");
}

BaseApp::BaseApp(unsigned int window_width, unsigned int window_height, std::string name) {
    this->window_width = window_width;
    this->window_height = window_height;
    this->window_name = name;
    this->main_camera = NULL;
}

BaseApp::~BaseApp() {
    glfwTerminate();
    if (main_camera) {
        delete main_camera;
    }
}

int BaseApp::Initialize() {
    // initializing glfw
    if (!glfwInit()) {
        std::cerr << "Initialization of GLFW failed." << std::endl;
        glfwTerminate();
        return 1;
    }

    // making a window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // I'm going to be working with 3.3+ functionality I think
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    this->window = glfwCreateWindow(this->window_width, this->window_height, "Teapot Explosion", NULL, NULL);
    if (!this->window) {
        std::cerr << "Failed to create window." << std::endl;
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(this->window);
    checkGLError("After making window context.", __FILE__, __LINE__);

    // initializing glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew." << std::endl;
        glfwTerminate();
        return 3;
    }
    checkGLError("After glew init.", __FILE__, __LINE__);

    // clear screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    checkGLError("Finished setup.", __FILE__, __LINE__);

    return 0;
}

void BaseApp::Run() {
    // main loop
    while (!glfwWindowShouldClose(this->window)) {
        // clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        //this->main_camera.Draw(this->scene);

        // swap the buffers after drawing
        glfwSwapBuffers(this->window);
        // poll the events to trigger any callbacks or key events
        glfwPollEvents();
    }
}
