#pragma once
#include <string>

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "settings.h"
#include "scene/Scene.h"


class Window
{
	int _width {SCR_WIDTH}, _height {SCR_HEIGHT};
	std::string _title{ "Demo" };
	static Window _instance;
	GLFWwindow* _window;
	bool _isCursorActive{ false };
	float lastFPSUpdate{ 0.0f };
	const float refreshFPSPeriod{ 0.5f };
	float FPS{ 60.0f };

	Window();
	Scene* currentScene {nullptr};

public:
	static Window& get();
	static void run();
	static void setScene(int scene);
	static void close();
	static GLFWwindow* getWindow();

	static void setClearColor(glm::vec3 color);

	static void switchCursorActive();
	static void setCursorActive();
	static void setCursorInactive();

	static void setCallbacks();
	static void unsetCallbacks();

private:
	static void updateFPS();
};

