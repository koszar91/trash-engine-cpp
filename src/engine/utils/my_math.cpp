#include <engine/utils/my_math.h>


glm::vec3 my_rotate(glm::vec3 a_vector, glm::vec3 a_axis, float a_angle)
{
	return a_vector * cosf(a_angle) +
		(glm::cross(a_axis, a_vector)) * sinf(a_angle) +
		a_axis * (glm::dot(a_axis, a_vector)) * (1 - cosf(a_angle));
}

float angle_between(glm::vec3 v1, glm::vec3 v2)
{
	return acosf(glm::dot(v1, v2) / (glm::length(v1) * glm::length(v2)));
}

float sgn(float x)
{
	if (x > 0) return  1;
	if (x < 0) return -1;
	return 0;
}

glm::vec3 coeffMultiply(glm::vec3 v1, glm::vec3 v2)
{
	return glm::vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

glm::vec3 coeffSquare(glm::vec3 v)
{
	return coeffMultiply(v, v);
}

glm::vec3 lineIntersection(glm::vec3 v1, glm::vec3 v2)
{
	// im ignoring the Y dimension, so it's really 2D :)
	// im also ignoring the possibility that the lines can be parallel :)
	
	// compute two points on each line
	glm::vec3 p1 = v1, p2 = v2 * 2.0f;
	glm::vec3 p3 = v1, p4 = v2 * 2.0f;

	// compute intersection point from wikipedia formula
	float d = (p1.x - p2.x) * (p3.z - p4.z)
			- (p1.z - p2.z) * (p3.x - p4.x);

	float x = (p1.x * p2.z - p1.z * p2.x) * (p3.x - p4.x)
			- (p1.x - p2.x) * (p3.x * p4.z - p3.z * p4.x);
	float z = (p1.x * p2.z - p1.z * p2.x) * (p3.z - p4.z)
			- (p1.z - p2.z) * (p3.x * p4.z - p3.z * p4.x);

	return glm::vec3(x / d, 0, z / d);
}
