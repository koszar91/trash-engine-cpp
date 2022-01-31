#pragma once


#include "Model.h"
#include "engine/utils/HeightMap.h"
#include <assimp/scene.h>

#include "ModelInstanced.h"


// for index buffers
struct triangle_i {
	unsigned int indexes[3];
};

struct square_i
{
	triangle_i triangles[2];
};


// for vertex buffers not using index buffers
struct triangle_v {
	vertex vertices[3];
};

struct square_v
{
	triangle_v triangles[2];
};


class ModelBuilder
{
	std::string tmpDirectory{};
	std::vector<Mesh> tmpMeshes{};
	std::vector<Texture> tmpLoadedTextures{};

	const static std::string modelsPath; // init in .cpp file

public:
	ModelBuilder() = default;

	Model buildFromHeightMap(float a_width, float a_height, HeightMap &a_map);
	Model buildFromFile(std::string a_name);
	ModelInstanced buildInstancedFromFile(std::string a_name, std::vector<Transform> a_transforms);

private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

