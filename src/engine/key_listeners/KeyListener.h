#pragma once
#include <GLFW/glfw3.h>

class KeyListener
{
	KeyListener() {}
	static KeyListener _instance;
	static constexpr int N_KEYS {350};
	bool keysPressed[N_KEYS] {false};
	double lastTimeKeysClicked[N_KEYS]{ 0.0 };
	const double CLICK_DURATION{ 0.3 };

public:
	static KeyListener& get();

	static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);

	static bool isKeyPressed(int key);
	static bool wasKeyClicked(int key);
};

