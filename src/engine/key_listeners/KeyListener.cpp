#include "KeyListener.h"


KeyListener KeyListener::_instance;


KeyListener& KeyListener::get()
{
	return _instance;
}

void KeyListener::keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		get().keysPressed[key] = true;
		get().lastTimeKeysClicked[key] = glfwGetTime();

	}
	else if (action == GLFW_RELEASE)
	{
		get().keysPressed[key] = false;
	}
}

bool KeyListener::isKeyPressed(int key)
{
	return get().keysPressed[key] ? key < N_KEYS : false;
}

bool KeyListener::wasKeyClicked(int key)
{
	return glfwGetTime() - get().lastTimeKeysClicked[key] > get().CLICK_DURATION ? false : true;
}
