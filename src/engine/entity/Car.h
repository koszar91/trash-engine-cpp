#pragma once


#include "entity.h"


struct Car : Entity
{
	// 1.5, 3.5, 1.7
	float length_rear, length_front;
	float wheel_base;
	float cor_stiff_rear, cor_stiff_front;

	float engine_force = 13000.0f;
	float braking_force = 10000.0f;

	Car(Transform a_transform, Model* a_model, Shader* a_shader, RigidBody* a_rigid_body);

};