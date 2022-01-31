#ifndef TRASHENGINE_CAMERA_H
#define TRASHENGINE_CAMERA_H


#include <glm/glm.hpp>


class Camera {

    glm::vec3 pos {0.0f, 0.0f, 0.0f};

	glm::vec3 front   {0.0f, 0.0f, -1.0f};
    glm::vec3 up      {0.0f, 1.0f, 0.0f };
    glm::vec3 right   {1.0f, 0.0f, 0.0f };
    glm::vec3 worldUp {0.0f, 1.0f, 0.0f };

	float pitch {0}, yaw {90};

    void recalculate();

public:
    Camera();
    Camera(glm::vec3 pos);

    void setPosition(glm::vec3 pos);
    void setFront(glm::vec3 fr);

    void moveForward(float dist);
    void moveRight(float dist);
    void moveUp(float dist);

    void addPitch(float dp);
    void addYaw(float dy);

    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;

};


#endif //TRASHENGINE_CAMERA_H
