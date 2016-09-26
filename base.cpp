#include "base.h"
#include "errors.h"

void glfw_error_cb(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}
void glfw_window_close_cb(GLFWwindow *window) {
    std::cout << "Window close" << std::endl;
}
void glfw_key_cb(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cout << "KEYPRESS_CB" << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else {
        std::cout << "key pressed: " << key << std::endl;
    }
}

void Run(GLFWwindow *window) {
    int loop_breaker = 0;
    // main loop
    while (!glfwWindowShouldClose(window) && loop_breaker++ < 500) {
        std::cout << "Time " << loop_breaker << ": " << glfwGetTime() << std::endl;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);

        int exit_state = glfwGetKey(window, GLFW_KEY_ESCAPE);
        if (exit_state) {
            glfwSetWindowShouldClose(window, GL_TRUE);
            std::cout << "key pressed: " << GLFW_KEY_ESCAPE << std::endl;
        }
    }
}

int main() {
    // initializing glfw
    if (!glfwInit()) {
        std::cerr << "Initialization of GLFW failed." << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwSetErrorCallback(glfw_error_cb);

    // making a window
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // I'm going to be working with 3.3+ functionality I think
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Teapot Explosion", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window." << std::endl;
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);
    checkGLError("After making window context.", "Run", __LINE__);

    // initializing glew
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew." << std::endl;
        glfwTerminate();
        return 3;
    }
    checkGLError("After glew init.", "Run", __LINE__);

    glfwSetWindowCloseCallback(window, glfw_window_close_cb);
    glfwSetKeyCallback(window, glfw_key_cb);

    checkGLError("Finished setup.", "Run", __LINE__);

    // run the main application
    Run(window);

    // terminate glfw and return
    glfwTerminate();
    return 0;
}
