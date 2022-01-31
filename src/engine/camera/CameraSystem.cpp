#include "CameraSystem.h"


void CameraSystem::update(Car car, Camera camera, float dt)
{
	glm::vec3 currCamPosition = camera.getPosition();
	glm::vec3 currCamOrientation = camera.getFront();

	glm::vec3 tagetCamPosition = car.transform.position - (car.transform.orientation() * 7.0f) + glm::vec3(0, 3.3, 0);
	glm::vec3 targetCamOrientation = car.transform.orientation() - glm::vec3(0, 0.15, 0);

	glm::vec3 resultCamPosition;
	glm::vec3 resultCamOrientation;

	switch (mode)
	{
	case CameraMode::STIFF:
	{
		resultCamPosition = tagetCamPosition;
		resultCamOrientation = targetCamOrientation;
		break;
	}


	case CameraMode::LERP:
	{
		resultCamPosition = currCamPosition + (tagetCamPosition - currCamPosition) * posLerpCoeff * dt;
		resultCamOrientation = currCamOrientation + (targetCamOrientation - currCamOrientation) * orientLerpCoeff * dt;
		break;
	}
	}

	camera.setPosition(resultCamPosition);
	camera.setFront(resultCamOrientation);
}
