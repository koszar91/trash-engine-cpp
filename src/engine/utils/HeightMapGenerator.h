#pragma once
#include <glm/vec2.hpp>

#include "HeightMap.h"


class HeightMapGenerator
{
public:
	static HeightMap genRandom(int wRes, int hRes);
	static HeightMap genCosSin(int wRes, int hRes);
	static HeightMap genPerlin(glm::vec2 offset, glm::vec2 res,
		int octaves, float scale, float lacunarity, float persistence);
};

