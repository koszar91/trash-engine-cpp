#pragma once
#include <assimp/defs.h>


enum class SteeringMode { KEYBOARD, STEERING_WHEEL };


class SteeringInputManager
{
	const float MAX_STEERING_ANGLE = AI_MATH_PI / 4.0f;

	float steeringAngle{ 0 };
	float accPedalValue{ 0 };
	float brkPedalValue{ 0 };

	SteeringMode steeringMode{SteeringMode::KEYBOARD };

public:
	void setSteeringMode(SteeringMode mode) { this->steeringMode = mode; }

	void collectInput();

	float steering() const { return steeringAngle; }

	float acc() const { return accPedalValue; }

	float brk() const { return brkPedalValue; }
};

