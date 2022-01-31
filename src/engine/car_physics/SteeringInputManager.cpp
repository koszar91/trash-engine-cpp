#include "SteeringInputManager.h"

#include <assimp/defs.h>

#include "engine/key_listeners/KeyListener.h"


void SteeringInputManager::collectInput()
{
	steeringAngle = 0;
	accPedalValue = 0;
	brkPedalValue = 0;

	switch (steeringMode)
	{
	case SteeringMode::KEYBOARD :
		{
		if (KeyListener::isKeyPressed(GLFW_KEY_A)) steeringAngle += AI_MATH_PI / 6.0f;
		if (KeyListener::isKeyPressed(GLFW_KEY_D)) steeringAngle -= AI_MATH_PI / 6.0f;
		if (KeyListener::isKeyPressed(GLFW_KEY_W)) accPedalValue = 1;
		if (KeyListener::isKeyPressed(GLFW_KEY_SPACE)) brkPedalValue = 1;
		break;
		}

	case SteeringMode::STEERING_WHEEL :
		{
		int nJoystickAxes;
		const float* joystickAxesValues = glfwGetJoystickAxes(0, &nJoystickAxes);
		steeringAngle = -joystickAxesValues[0] * MAX_STEERING_ANGLE;
		accPedalValue = -joystickAxesValues[1] * 0.5f + 0.5f;
		brkPedalValue = -joystickAxesValues[2] * 0.5f + 0.5f;
		break;
		}
	}
}
