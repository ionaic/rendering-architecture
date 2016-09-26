#include "base.h"
#include "meshloader.h"


void glfw_error_cb(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}
void glfw_window_close_cb(GLFWwindow *window) {
    std::cout << "Window close" << std::endl;
}
void glfw_key_cb(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
void glfw_mouse_button_cb(GLFWwindow *window, int button, int action, int mods) {
    std::cout << "MOUSE CLICK" << std::endl;
}
void glfw_mouse_position_cb(GLFWwindow *window, double xpos, double ypos) {
    std::cout << "MOUSE POS: (" << xpos << ", " << ypos << ")" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Must provide filename of Utah Teapot file" << std::endl;
    }
    BaseApp base;
    
    // set glfw error callback
    glfwSetErrorCallback(glfw_error_cb);

    // initialize the base application object
    int err = base.Initialize();
    if (err != 0) {
        return err;
    }
    // set window close and key callbacks
    glfwSetWindowCloseCallback(base.window, glfw_window_close_cb);
    glfwSetKeyCallback(base.window, glfw_key_cb);
    glfwSetMouseButtonCallback(base.window, glfw_mouse_button_cb);
    glfwSetCursorPosCallback(base.window, glfw_mouse_position_cb);

    // load the mesh
    OBJMeshLoader mesh_loader(std::string(argv[1]));
    
    // run the main application
    base.Run();

    return 0;
}
