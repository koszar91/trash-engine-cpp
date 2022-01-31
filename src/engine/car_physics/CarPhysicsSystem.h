#pragma once
#include "SteeringInputManager.h"
#include "engine/entity/Car.h"


class CarPhysicsSystem
{
	SteeringInputManager inputManager{ };

	const float DRAG = 150.0f;
	const float ROLL_RESIST = 410.0f;


public:
	void update(Car& car, float dt);

};

