#include "RigidBody.h"

RigidBody::RigidBody(float mass, float inertia)
	: mass(mass), inertia(inertia)
{
}

void RigidBody::integrate(Transform& transform, float dt)
{
	// translational movement
	acceleration = net_force / mass;
	velocity += acceleration * dt;
	if (speed() <= CLAMP_VALUE && acc_length() <= CLAMP_VALUE )
		velocity = glm::vec3(0);
	transform.position += velocity * dt;

	// rotational movement
	angular_acceleration = net_torque / inertia;
	angular_velocity += angular_acceleration * dt;
	if (angular_speed() <= CLAMP_VALUE && angular_acc_length() <= CLAMP_VALUE)
		angular_velocity = glm::vec3(0);
	transform.rotation += angular_velocity * dt;
}

void RigidBody::clean()
{
	net_force = glm::vec3(0);
	net_torque = glm::vec3(0);
}
