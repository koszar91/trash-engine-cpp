#include "HeightMapGenerator.h"

#include <iostream>
#include <random>
#include <GLFW/glfw3.h>

#include "PerlinNoise.h"


HeightMap HeightMapGenerator::genPerlin(glm::vec2 offset, glm::vec2 res,
	int octaves, float scale, float lacunarity, float persistence)
{
	PerlinNoise pn {(unsigned int)glfwGetTime()};

	float hMin = FLT_MAX;
	float hMax = FLT_MIN;

	auto data = new float* [res.x];
	for (int x = 0; x < res.x; x++)
	{
		data[x] = new float[res.y];
		for (int z = 0; z < res.y; z++)
		{

			float amplitude = 10;
			float frequency = 1;
			float height = 0;

			// add each octave
			for (int o=0; o < octaves; o++)
			{
				float xSample = x * scale * frequency + o * 1e5 + offset.x;
				float zSample = z * scale * frequency + o * 1e5 + offset.y;

				float noise = pn.noise(xSample, zSample, 1e5);
				height += noise * amplitude;

				amplitude *= persistence;
				frequency *= lacunarity;
			}

			data[x][z] = height;
			hMin = std::min(height, hMin);
			hMax = std::max(height, hMax);
		}
	}

	float hAvg = (hMax + hMin) / 2.0f;
	for (int x = 0; x < res.x; x++) for (int z = 0; z < res.y; z++)
	{
		data[x][z] -= hAvg;
		hMin = std::min(data[x][z], hMin);
		hMax = std::max(data[x][z], hMax);
	}

	return HeightMap{ (int) res.x, (int) res.y, hMax, hMin, data };
}
