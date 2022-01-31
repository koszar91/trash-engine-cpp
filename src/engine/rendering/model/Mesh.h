#pragma once
#include <glm/glm.hpp>
#include <string>

#include "engine/rendering/Shader.h"


struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};


struct Texture {
    unsigned int id;
    std::string type;
    std::string path;

    Texture(const char* path, const std::string& directory, std::string& typeName);
};

struct Material {
    glm::vec3 ambient, diffuse, specular;
    float shininess;

    bool useDiffuseMap, useSpecularMap;
    std::vector<Texture> diffuseMaps, specularMaps;
};


struct Mesh {

    unsigned int VAO{}, VBO{}, EBO{};
    int vCount, iCount;
	vertex* vertices;
    unsigned int* indices;
    Material material;

    Mesh(vertex vertices[], int vCount, unsigned int indices[], int iCount, Material mat);
    ~Mesh();
    void Draw(Shader& shader) const;
    void DrawInstanced(Shader& shader, int count) const;

private:
    void setupMesh();
};