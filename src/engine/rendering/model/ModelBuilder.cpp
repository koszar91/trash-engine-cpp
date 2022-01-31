#include "ModelBuilder.h"

#include <random>
#include <iostream>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <stb_image.h>


const std::string ModelBuilder::modelsPath = "res/models";


Model ModelBuilder::buildFromHeightMap(float a_width, float a_height, HeightMap& a_map)
{
	float wRes = a_map.wRes;
	float hRes = a_map.hRes;
	float squareWidth = a_width / (wRes - 1.0f);
	float squareHeight = a_height / (hRes - 1.0f);
	std::vector<square_v> squares((int) (wRes - 1.0f) * (hRes - 1.0f));
	for (int z = 0; z < hRes - 1; z++)
	{
		for (int x = 0; x < wRes - 1; x++)
		{
			// triangle 1
			glm::vec3 positions1[3] = {
				{x * squareWidth - a_width / 2.0f,a_map.sample(x /  wRes, z /  hRes), z * squareHeight - a_height / 2.0f},
				{ x * squareWidth - a_width / 2.0f,a_map.sample(x / wRes, (z+1) / hRes), (z + 1) * squareHeight - a_height / 2.0f },
				{(x + 1) * squareWidth - a_width / 2.0f,a_map.sample((x + 1) / wRes, z / hRes), z * squareHeight - a_height / 2.0f }
			};
			squares[x + z * (hRes - 1)].triangles[0].vertices[0].position = positions1[0];
			squares[x + z * (hRes - 1)].triangles[0].vertices[1].position = positions1[1];
			squares[x + z * (hRes - 1)].triangles[0].vertices[2].position = positions1[2];
			glm::vec3 normal1 = glm::normalize(glm::cross(positions1[1] - positions1[0], positions1[2] - positions1[0]));
			squares[x + z * (hRes - 1)].triangles[0].vertices[0].normal = normal1;
			squares[x + z * (hRes - 1)].triangles[0].vertices[1].normal = normal1;
			squares[x + z * (hRes - 1)].triangles[0].vertices[2].normal = normal1;

			// triangle 2
			glm::vec3 positions2[3] = {
				positions1[2],
				positions1[1],
				{(x + 1) * squareWidth - a_width / 2.0f,a_map.sample((x + 1) / wRes, (z + 1) / hRes), (z + 1) * squareHeight - a_height / 2.0f }
			};
			squares[x + z * (hRes - 1)].triangles[1].vertices[0].position = positions2[0];
			squares[x + z * (hRes - 1)].triangles[1].vertices[1].position = positions2[1];
			squares[x + z * (hRes - 1)].triangles[1].vertices[2].position = positions2[2];
			glm::vec3 normal2 = glm::normalize(glm::cross(positions2[1] - positions2[0], positions2[2] - positions2[0]));
			squares[x + z * (hRes - 1)].triangles[1].vertices[0].normal = normal2;
			squares[x + z * (hRes - 1)].triangles[1].vertices[1].normal = normal2;
			squares[x + z * (hRes - 1)].triangles[1].vertices[2].normal = normal2;

		}
	}

	auto vertices = new vertex[squares.size() * 6];
	memcpy(vertices, squares.data(), squares.size() * sizeof(square_v));

	// create material
	Material material;
	material.ambient = {0.21, 0.30, 0.21};
	material.diffuse = {0.30, 0.56, 0.30};
	material.specular = {0.18, 0.18, 0.18};
	material.shininess = 1;
	material.specularMaps = std::vector<Texture>();
	material.diffuseMaps = std::vector<Texture>();
	material.useSpecularMap = false;
	material.useDiffuseMap = false;

	std::vector<Mesh> resultMeshes {};
	resultMeshes.push_back(Mesh(vertices, 6 * squares.size(), nullptr, 0, material));
	return Model(resultMeshes);
}

Model ModelBuilder::buildFromFile(std::string a_name)
{
	std::string path(modelsPath + "/" + a_name + "/" + a_name + ".obj");

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		exit(1);
	}
	tmpDirectory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);

	std::vector<Mesh> resultMeshes = std::move(tmpMeshes);
	tmpMeshes.clear();

	return Model(resultMeshes);
}

ModelInstanced ModelBuilder::buildInstancedFromFile(std::string a_name, std::vector<Transform> a_transforms)
{
	std::string path(modelsPath + "/" + a_name + "/" + a_name + ".obj");

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		exit(1);
	}
	tmpDirectory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);

	std::vector<Mesh> resultMeshes = std::move(tmpMeshes);
	tmpMeshes.clear();

	return ModelInstanced(resultMeshes, a_transforms);
}


void ModelBuilder::processNode(aiNode* node, const aiScene* scene) {
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		tmpMeshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh ModelBuilder::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	Material mat;

	// process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		vertex v;
		v.position = glm::vec3(mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z);
		if (mesh->mNormals) {
			v.normal = glm::vec3(mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z);
		}
		else {
			v.normal = glm::vec3(0);
		}

		if (mesh->mTextureCoords[0]) {
			v.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y);
		}
		else {
			v.texCoords = glm::vec2(0);
		}
		vertices.push_back(v);
	}

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process material
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// colors
		aiColor3D ambColor;
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambColor);
		aiColor3D diffColor;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffColor);
		aiColor3D specColor;
		material->Get(AI_MATKEY_COLOR_SPECULAR, specColor);
		float shininess;
		material->Get(AI_MATKEY_SHININESS, shininess);

		mat.ambient = glm::vec3(ambColor.r, ambColor.g, ambColor.b);
		mat.diffuse = glm::vec3(diffColor.r, diffColor.g, diffColor.b);
		mat.specular = glm::vec3(specColor.r, specColor.g, specColor.b);
		mat.shininess = shininess;

		// textures
		// 1. diffuse maps
		mat.diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		mat.useDiffuseMap = true ? !mat.diffuseMaps.empty() : false;
		// 2. specular maps
		mat.specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		mat.useSpecularMap = true ? !mat.specularMaps.empty() : false;
	}


	return Mesh(vertices.data(), vertices.size(), indices.data(), indices.size(), mat);
}

std::vector<Texture> ModelBuilder::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		// check if loading more than 1
		if (i > 1)
		{
			std::cout << "Loading model '" << tmpDirectory << "', one of the meshes has "
				<< std::to_string(i) << "'th " << typeName << " texture! It won't be used." << std::endl;
		}

		// check whether it's already loaded
		bool isLoaded = false;

		aiString textureName;
		mat->GetTexture(type, i, &textureName);
		for (unsigned int j = 0; j < tmpLoadedTextures.size(); j++)
		{
			if (std::strcmp(tmpLoadedTextures[j].path.data(), textureName.C_Str()) == 0)
			{
				textures.push_back(tmpLoadedTextures[j]);
				isLoaded = true;
				break;
			}
		}
		if (!isLoaded)
		{   // if texture hasn't been loaded already, load it
			Texture texture(textureName.C_Str(), tmpDirectory, typeName);
			textures.push_back(texture);
			tmpLoadedTextures.push_back(texture); // add to loaded textures
		}
	}
	return textures;
}