#pragma once

#include "glm/glm.hpp"


class MouseListener {

    MouseListener();
    static MouseListener _instance;

    glm::vec2 scroll {0.0f, 0.0f};
    glm::vec2 currentPos {0.0f, 0.0f}; // changed in constructor, using glfw
    glm::vec2 previousPos {0.0f, 0.0f}; // this too

    bool buttonsPressed[3] {false};
    bool isDragging {false};


public:
    static MouseListener& get();

    static void mousePositionCallback(GLFWwindow* win, double x, double y);
    static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
	static void mouseScrollCallback(GLFWwindow* win, double xOffset, double yOffset);

	static void frameEnded();

    static glm::vec2 getMousePosition();
    static glm::vec2 getMouseMove();
    static glm::vec2 getMouseScroll();
    static bool isMouseDragging();
    static bool isMouseButtonPressed(int button);
};


