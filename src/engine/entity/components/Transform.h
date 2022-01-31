#pragma once
#include <glm/glm.hpp>


struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();
	Transform(glm::vec3 a_position);
	Transform(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale);

	glm::mat4 modelMatrix() const;
	glm::vec3 orientation() const;
};
