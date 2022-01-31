#pragma once


#include "glm/glm.hpp"


glm::vec3 my_rotate(glm::vec3 a_vector, glm::vec3 a_axis, float a_angle);

float angle_between(glm::vec3 v1, glm::vec3 v2);

float sgn(float x);

glm::vec3 coeffMultiply(glm::vec3 v1, glm::vec3 v2);

glm::vec3 coeffSquare(glm::vec3 v);

glm::vec3 lineIntersection(glm::vec3 v1, glm::vec3 v2);
