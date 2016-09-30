#include "scene.h"

#include <iterator>

Transform::Transform() {}

void Transform::Translate(glm::vec3 move) {
    this->position = glm::vec4(move.x, move.y, move.z, 1.0f);
}

void Transform::Rotate(glm::vec3 axis, float angle) {

}

void Transform::Scale(glm::vec3 factors) {
    this->scale = factors;
}

void Transform::Scale(float x, float y, float z) {
    this->scale = glm::vec3(x, y, z);
}

glm::mat4 Transform::GetMatrix() const {
    // combine into one array
    std::vector<float> tmp;

    // apply the rotation to our vector basis
    glm::vec4 up_ = glm::rotate(rotation, this->basis.up);
    glm::vec4 left_ = glm::rotate(rotation, this->basis.left);
    glm::vec4 forward_ = glm::rotate(rotation, this->basis.forward);

    // insert each vec4 at the end of the tmp vector
    tmp.insert(std::end(tmp), glm::value_ptr(left_), glm::value_ptr(left_) + 4);
    tmp.insert(std::end(tmp), glm::value_ptr(up_), glm::value_ptr(up_) + 4);
    tmp.insert(std::end(tmp), glm::value_ptr(forward_), glm::value_ptr(forward_) + 4);
    tmp.insert(std::end(tmp), glm::value_ptr(this->position), glm::value_ptr(this->position) + 4);

    glm::mat4 out = glm::make_mat4(&tmp[0]);

    //out *= glm::translate(this->position);
    out *= glm::scale(this->scale);

    return out;
}
