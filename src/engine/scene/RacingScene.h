#pragma once


#include <glm/ext/matrix_clip_space.hpp>

#include "Scene.h"
#include "engine/settings.h"
#include "engine/camera/Camera.h"
#include "engine/car_physics/CarPhysicsSystem.h"
#include "engine/entity/Car.h"
#include "engine/entity/components/RigidBody.h"
#include "engine/entity/components/Transform.h"
#include "engine/entity/Entity.h"
#include "engine/rendering/model/ModelBuilder.h"


class RacingScene : public Scene
{
	float fov{ 60.0f }, aspectRatio{ (float)SCR_WIDTH / (float)SCR_HEIGHT };
	const float Z_NEAR{ 0.1f }, Z_FAR{ 1000.0f };
	glm::mat4 proj{ glm::perspective(glm::radians(fov), aspectRatio, Z_NEAR, Z_FAR) };
	ModelBuilder mb{ };

	Shader basicShader { };
	Model trackModel{ mb.buildFromFile("my_track") };
	Model carModel{ mb.buildFromFile("ford") };


	Entity track{ Transform(), &trackModel, &basicShader };
	Car car{ Transform(glm::vec3(58.0f, 0.0f, 2.0f)), &carModel, &basicShader, new RigidBody(1000, 2400) };

	CarPhysicsSystem carSystem{};


public:
	RacingScene();
	~RacingScene() override;

	void update(float dt) override;
	void updateImGui(float dt) override;
	void render(float dt) override;

private:
	void updateCameraToFollowCar(int mode, glm::vec3 carPosition, glm::vec3 carOrientation, float dt);
};


