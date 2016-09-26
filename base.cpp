#include "base.h"

BaseApp::BaseApp() {
    BaseApp(640, 480);
}

BaseApp::BaseApp(unsigned int window_width, unsigned int window_height) {

}

BaseApp::~BaseApp() {
    glfwTerminate();
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
    this->window = glfwCreateWindow(640, 480, "Teapot Explosion", NULL, NULL);
    if (!this->window) {
        std::cerr << "Failed to create window." << std::endl;
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(this->window);
    checkGLError("After making window context.", "BaseApp Initialize", __LINE__);

    // initializing glew
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew." << std::endl;
        glfwTerminate();
        return 3;
    }
    checkGLError("After glew init.", "BaseApp Initialize", __LINE__);

    // clear screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    checkGLError("Finished setup.", "BaseApp Initialize", __LINE__);

    return 0;
}

void BaseApp::Run() {
    // main loop
    while (!glfwWindowShouldClose(this->window)) {
        // clear the screen
        glClear(GL_COLOR_BUFFER_BIT);


        // swap the buffers after drawing
        glfwSwapBuffers(this->window);
        // poll the events to trigger any callbacks or key events
        glfwPollEvents();
    }
}
