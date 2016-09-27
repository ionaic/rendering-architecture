#include "scene.h"

Transform::Transform() {}

Transform::Translate(glm::vec3 move) {

}

void Transform::Rotate(glm::vec3 axis, float angle) {

}

void Transform::Scale(float factor) {
    this->scale = factor;
}

glm::mat4 GetMatrix() {
    // combine into one array
    std::vector<float> tmp;

    // apply the rotation to our vector basis
    glm::vec4 up_ = glm::gtx::quaternion::rotate(rotation, this->up);
    glm::vec4 left_ = glm::gtx::quaternion::rotate(rotation, this->left);
    glm::vec4 forward_ = glm::gtx::quaternion::rotate(rotation, this->forward);

    // insert each vec4 at the end of the tmp vector
    tmp.insert(std::end(tmp), std::begin(left_), std::end(left_));
    tmp.insert(std::end(tmp), std::begin(up_), std::end(up_));
    tmp.insert(std::end(tmp), std::begin(forward_), std::end(forward_));

    glm::mat4 out = glm::gtc::make_mat4(&tmp[0]);

    out *= glm::gtx::transform::translate(this->position);
    out *= glm::gtx::transform::scale(this->scale);

    return out;
}
