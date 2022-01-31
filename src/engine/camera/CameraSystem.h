#pragma once
#include "Camera.h"
#include "engine/entity/Car.h"

enum class CameraMode { STIFF, LERP };

class CameraSystem
{
	CameraMode mode{ CameraMode::LERP };
	glm::vec3 targetCamPosOffset{ -7, 3.3, 0 };
	glm::vec3 targetCamOrientOffset{ 0, -0.15, 0 };

	float posLerpCoeff = 2.7f;
	float orientLerpCoeff = 1.7f;

	void update(Car car, Camera camera, float dt);
};

