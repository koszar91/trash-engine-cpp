#include "Scene.h"

#include <glm/vec2.hpp>

#include "engine/key_listeners/KeyListener.h"
#include "engine/key_listeners/MouseListener.h"

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::updateCameraBasedOnMouse(float dt)
{
    // update looking direction based on mouse
    
    glm::vec2 mouseMove(MouseListener::getMouseMove());
    camera.addPitch(mouseMove.y * mouseSensitivity);
    camera.addYaw(mouseMove.x * mouseSensitivity);
    


    // update position based on WSAD, space, shift
    if (KeyListener::isKeyPressed(GLFW_KEY_W))
        camera.moveForward(cameraMoveSpeed * (float)dt);
    if (KeyListener::isKeyPressed(GLFW_KEY_S))
        camera.moveForward(-cameraMoveSpeed * (float)dt);
    if (KeyListener::isKeyPressed(GLFW_KEY_A))
        camera.moveRight(-cameraMoveSpeed * (float)dt);
    if (KeyListener::isKeyPressed(GLFW_KEY_D))
        camera.moveRight(cameraMoveSpeed * (float)dt);
    if (KeyListener::isKeyPressed(GLFW_KEY_SPACE))
        camera.moveUp(cameraMoveSpeed * (float)dt);
    if (KeyListener::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
        camera.moveUp(-cameraMoveSpeed * (float)dt);
}
