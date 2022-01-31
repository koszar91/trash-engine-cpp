#pragma once
#include <glm/ext/matrix_clip_space.hpp>
#include "engine/camera/Camera.h"
#include "Scene.h"
#include "engine/settings.h"
#include "engine/entity/Entity.h"
#include "engine/entity/components/Transform.h"
#include "engine/rendering/cubemap/Cubemap.h"
#include "engine/rendering/model/Model.h"
#include "engine/rendering/model/ModelBuilder.h"
#include "engine/utils/HeightMap.h"
#include "engine/utils/HeightMapGenerator.h"


class TerrainGenerationScene : public Scene
{
	float fov{ 60.0f }, aspectRatio{ (float) SCR_WIDTH / (float) SCR_HEIGHT };
	const float Z_NEAR{ 0.1f }, Z_FAR{ 1000.0f };
	glm::mat4 proj{ glm::perspective(glm::radians(fov), aspectRatio, Z_NEAR, Z_FAR) };
	ModelBuilder mb{ };

	// ASSETS (in future they will be moved into asset pool, bc they are supposed to be shared between entities)

	// 1.terrain map
	glm::vec2 mapRes{ START_RES };
	glm::vec2 mapOffset{ START_OFFSET };
	int octaves{ START_OCTAVES };
	float persistence{ START_PERSISTENCE };
	float lacunarity{ START_LACUNARITY };
	float scale{ START_SCALE };
	HeightMap terrainHeightMap{ HeightMapGenerator::genPerlin(mapOffset, mapRes,
		octaves, scale, lacunarity, persistence) };

	// 2.models
	std::vector<Transform> treesTransforms{ genTreesTransforms(100) };
	ModelInstanced instancedTreesModel{ mb.buildInstancedFromFile("my_tree", treesTransforms) };
	Model terrainModel{ mb.buildFromHeightMap(CHUNK_SIZE, CHUNK_SIZE, terrainHeightMap) };

	// 3.shaders
	Shader basicShader{ };
	Shader basicInstancedShader{ "basicInstanced.vs.glsl" };
	
	// 4.entities
	Entity terrain{ Transform(), &terrainModel, &basicShader};
	Entity* trees{ };

public:
	TerrainGenerationScene();
	~TerrainGenerationScene() override;
	
	
	void update(float dt) override;
	void render(float dt) override;
	void updateImGui(float dt) override;

private:
	std::vector<Transform> genTreesTransforms(int count);
};


