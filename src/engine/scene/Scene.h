#pragma once


#define TERRAIN_GEN_SCENE 0
#define RACING_SCENE 1
#include "engine/settings.h"
#include "engine/camera/Camera.h"


class Scene
{
public:
	Scene();
	virtual ~Scene();

	void virtual update(float dt) = 0;
	void virtual updateImGui(float dt) = 0;
	void virtual render(float dt) = 0;

protected:
	Camera camera{};
	bool isCameraActive{ true };
	float cameraMoveSpeed{ START_CAMERA_SPEED };
	float mouseSensitivity{ START_MOUSE_SENSITIVITY };

	void updateCameraBasedOnMouse(float dt);
};

