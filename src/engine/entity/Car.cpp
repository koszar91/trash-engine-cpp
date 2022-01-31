#include "Car.h"


Car::Car(Transform a_transform, Model* a_model, Shader* a_shader, RigidBody* a_rigid_body)
	: Entity(a_transform, a_model, a_shader, a_rigid_body),
	  length_rear(2), length_front(3), wheel_base(2),
	  cor_stiff_rear(3300), cor_stiff_front(3300)
{

}
