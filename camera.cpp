#include "camera.h"

Camera::Camera() {}
Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix() {
    // return identity for the moment
    return glm::mat4(1.0f);
}

void Camera::Draw(const SceneObject *scene) {
    //std::cout << "Camera Draw" << std::endl;
    scene->mesh->UseMesh();
    scene->shader.UseShader();
    //std::cout << "After using mesh/shader" << std::endl;
    
    checkGLError("before drawing elements", __FILE__, __LINE__);
    glDrawElements(GL_TRIANGLES, scene->mesh->indices.size(), GL_UNSIGNED_INT, 0);
    checkGLError("after drawing elements", __FILE__, __LINE__);
}
