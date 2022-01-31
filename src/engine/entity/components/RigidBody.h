#pragma once
#include <glm/vec3.hpp>

#include "Transform.h"


struct RigidBody
{
	// translational
	float mass{ 1000 };
	glm::vec3 velocity{0.0f };
	glm::vec3 acceleration{0.0f };
	glm::vec3 net_force{ 0.0f };

	// rotational
	float inertia{ 2400 };
	// all of the following three vectors are about (x-axis, y-axis, z-axis)
	glm::vec3 angular_velocity{ 0.0f };
	glm::vec3 angular_acceleration{ 0.0f };
	glm::vec3 net_torque{ 0.0f };

	const float CLAMP_VALUE = 0.5;

	RigidBody(float mass, float inertia);

	float speed() const { return glm::length(velocity); }
	float acc_length() const { return glm::length(acceleration); }
	float angular_speed() const { return glm::length(angular_velocity); }
	float angular_acc_length() const { return glm::length(angular_acceleration); }

	void integrate(Transform& transform, float dt);
	void clean();
};

