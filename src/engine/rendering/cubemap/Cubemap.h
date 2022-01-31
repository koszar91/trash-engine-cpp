#pragma once
#include <string>
#include <vector>

#include "engine/rendering/Shader.h"


class Cubemap
{

public:
	std::string name;
	unsigned int textureID;
	float verticesData[6 * 6 * 3];
	unsigned int VBO;
	unsigned int VAO;


	const static std::string cubemapsPath;
	const static std::vector<std::string> faces;

public:
	Cubemap(std::string name);

	void Draw(Shader& shader) const;

};

