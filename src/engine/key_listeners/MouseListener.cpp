#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "MouseListener.h"

#include <iostream>

#include "engine/Window.h"


MouseListener MouseListener::_instance;


MouseListener::MouseListener()
{
    
}

MouseListener& MouseListener::get() {
    return _instance;
}

void MouseListener::mousePositionCallback(GLFWwindow* win, double x, double y) {
    get().previousPos = get().currentPos;
    get().currentPos = glm::vec2(x, y);

    get().isDragging = get().buttonsPressed[0] ||
					   get().buttonsPressed[1] ||
					   get().buttonsPressed[2];
}

void MouseListener::mouseButtonCallback(GLFWwindow* win, int button, int action, int mods)
{
    if (0 <= button < 3)
    {
        if (action == GLFW_PRESS)
        {
            get().buttonsPressed[button] = true;
        }
    	else if (action = GLFW_RELEASE)
        {
            get().isDragging = false;
            get().buttonsPressed[button] = false;
        }
    }
}
    

void MouseListener::mouseScrollCallback(GLFWwindow *win, double xOffset, double yOffset) {
    get().scroll = glm::vec2(xOffset, yOffset);
}

void MouseListener::frameEnded()
{
    get().scroll = glm::vec2(0.0f, 0.0f);
    get().previousPos = get().currentPos;
}

glm::vec2 MouseListener::getMousePosition()
{
    return get().currentPos;
}

glm::vec2 MouseListener::getMouseMove()
{
    return get().currentPos - get().previousPos;
}

glm::vec2 MouseListener::getMouseScroll()
{
    return get().scroll;
}

bool MouseListener::isMouseDragging()
{
    return get().isDragging;
}

bool MouseListener::isMouseButtonPressed(int button)
{
    return get().buttonsPressed[button] ? 0 <= button < 3 : false;
}



