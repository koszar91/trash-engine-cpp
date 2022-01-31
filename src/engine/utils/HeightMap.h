#pragma once


struct HeightMap
{
	int wRes, hRes;
	float hMax, hMin;
	float** data;

	// Assumes that arguments are in range [0, 1)
	[[nodiscard]]
	float sample(float x, float z) const
	{
		return data[static_cast<int>(x * wRes)][static_cast<int>(z * hRes)];
	}
};

