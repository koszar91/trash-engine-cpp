#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>


Transform::Transform(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale)
	: position(a_position), rotation(a_rotation), scale(a_scale)
{

}

Transform::Transform() : Transform(glm::vec3(0), glm::vec3(0), glm::vec3(1))
{

}

Transform::Transform(glm::vec3 a_position) : Transform(a_position, glm::vec3(0), glm::vec3(1))
{

}


glm::mat4 Transform::modelMatrix() const
{
	glm::mat4 T(glm::translate(glm::mat4(1.0f), position));

	glm::mat4 Rx(glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)));
	glm::mat4 Ry(glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::mat4 Rz(glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)));

	glm::mat4 S(glm::scale(glm::mat4(1.0f), scale));

	return T * Rz * Ry * Rx * S;
}

// assumes that front is the +Z axis
glm::vec3 Transform::orientation() const
{
	glm::vec3 orientation(0.0f, 0.0f, 1.0f);
	glm::mat4 Rx(glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)));
	glm::mat4 Ry(glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::mat4 Rz(glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)));
	return glm::normalize(glm::vec3(Rz * Ry * Rx * glm::vec4(orientation, 0.0f)));
	
}
