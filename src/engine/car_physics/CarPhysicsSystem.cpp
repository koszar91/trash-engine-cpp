#include "CarPhysicsSystem.h"

#include "engine/utils/my_math.h"


void CarPhysicsSystem::update(Car& car, float dt)
{
	// collect player's input
	inputManager.collectInput();

	// clean up forces and moments
	car.rigid_body->clean();


	// calculate longitudinal forces
	glm::vec3 long_dir = car.transform.orientation();
	float long_vel = dot(car.rigid_body->velocity, long_dir);
	float long_force = inputManager.acc() * car.engine_force;
	car.rigid_body->net_force += long_dir * long_force;

	// compute car frame directions and velocities
	glm::vec3 lateral_dir = my_rotate(long_dir, glm::vec3(0, 1, 0), AI_MATH_PI / 2.0f);
	float lateral_vel = dot(car.rigid_body->velocity, lateral_dir);

	// lateral force & aligning torque
	if (car.rigid_body->speed() > 0)
	{
		// get slip angles
		float slip_angle_front = atanf((lateral_vel + car.rigid_body->angular_velocity.y * car.length_front) / abs(long_vel))
			- inputManager.steering() * sgn(long_vel);
		float slip_angle_rear = atanf((lateral_vel - car.rigid_body->angular_velocity.y * car.length_rear) / abs(long_vel));

		// compute tire forces
		float rear_axle_force = -car.cor_stiff_rear * slip_angle_rear;
		float front_axle_force = -car.cor_stiff_front * slip_angle_front;

		// use tire forces to derive force acting on the car
		float lat_force = front_axle_force * cosf(inputManager.steering()) + rear_axle_force;

		// cornering force
		car.rigid_body->net_force += lateral_dir * lat_force;

		// aligning torque
		car.rigid_body->net_torque += glm::vec3(0, front_axle_force * car.length_front * cosf(inputManager.steering()), 0);
		car.rigid_body->net_torque += glm::vec3(0, -rear_axle_force * car.length_rear, 0);
	}


	// drag & air resistance, braking forces
	if (car.rigid_body->speed() > 0)
	{
		// drag force
		car.rigid_body->net_force -= DRAG * car.rigid_body->speed() * normalize(car.rigid_body->velocity);

		// rolling resistance force
		car.rigid_body->net_force -= ROLL_RESIST * normalize(car.rigid_body->velocity);

		// braking force
		car.rigid_body->net_force -= inputManager.brk() * car.braking_force * normalize(car.rigid_body->velocity);
	}


	// torque braking and drag
	if (car.rigid_body->angular_speed() > 0)
	{
		car.rigid_body->net_torque -= ROLL_RESIST * car.rigid_body->angular_speed() * normalize(car.rigid_body->angular_velocity);
		// car.rigid_body->net_torque -= inputManager.brk() * car.braking_force * normalize(car.rigid_body->angular_velocity);
	}

	

	car.rigid_body->integrate(car.transform, dt);
}

