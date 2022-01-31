#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera() {
    Camera(glm::vec3(0));
}

Camera::Camera(glm::vec3 pos) : pos(pos)
{
    recalculate();
}

void Camera::setPosition(glm::vec3 pos)
{
    this->pos = pos;
}

void Camera::setFront(glm::vec3 fr)
{
    this->front = fr;
}

void Camera::moveForward(float dist) {
    glm::vec3 dir = glm::vec3(cos(glm::radians(yaw)),
							  0,
							  sin(glm::radians(yaw)));
	pos += glm::normalize(dir) * dist;
}

void Camera::moveRight(float dist) {
    glm::vec3 dir = glm::vec3(cos(glm::radians(yaw)),
							  0,
							  sin(glm::radians(yaw)));
    glm::vec3 dirRight = glm::cross(glm::normalize(dir), worldUp);

	pos += glm::normalize(dirRight) * dist;
}

void Camera::moveUp(float dist) {
    pos += glm::vec3(0, dist, 0);
}


void Camera::addPitch(float dp) {
    float newPitch = pitch - dp;
    newPitch = std::fmin(newPitch, 89.0f);
    newPitch = std::fmax(newPitch, -89.0f);
    pitch = newPitch;
    recalculate();
}

void Camera::addYaw(float dy) {
    yaw += dy;
    recalculate();
}


glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(pos, pos + front, up);
}

void Camera::recalculate() {
    float x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    float y = sin(glm::radians(pitch));
    float z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(glm::vec3(x, y, z));

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::vec3 Camera::getPosition() const {
    return pos;
}

glm::vec3 Camera::getFront() const {
    return front;
}



