#include "GL/glew.h"
#include "Model.h"
#include "stb_image.h"
#include "engine/rendering/gl_utils.h"


Mesh::Mesh(vertex vertices[], int vCount, unsigned int indices[], int iCount, Material mat)
    : vCount(vCount), iCount(iCount), material(mat), vertices(vertices)
{

    if (iCount > 0)
    {
        this->indices = new unsigned int[iCount];
        memcpy(this->indices, indices, iCount * sizeof(unsigned int));
    }

	setupMesh();
}

Mesh::~Mesh()
{
    // delete(vertices);
    // if (iCount > 0) delete(indices);
}

void Mesh::Draw(Shader &shader) const {

    // enable shader
	shader.use();

    // load colors
    shader.setVec3("material.ambient", material.ambient);
    shader.setVec3("material.diffuse", material.diffuse);
    shader.setVec3("material.specular", material.specular);
    shader.setFloat("material.shininess", material.shininess);

    // bind textures

    if (material.useDiffuseMap) {
        shader.setBool("material.useDiffuseMap", true);
        glActiveTexture(GL_TEXTURE1);
        shader.setInt("material.diffuseMap", 1);
        glBindTexture(GL_TEXTURE_2D, material.diffuseMaps[0].id);
    } else {
        shader.setBool("material.useDiffuseMap", false);
    }
    if (material.useSpecularMap)
    {
        shader.setBool("material.useSpecularMap", true);
        glActiveTexture(GL_TEXTURE2);
        shader.setInt("material.specularMap", 2);
        glBindTexture(GL_TEXTURE_2D, material.specularMaps[0].id);
    } else
    {
        shader.setBool("material.useSpecularMap", false);
    }

    glActiveTexture(GL_TEXTURE0);


    // draw mesh
    glBindVertexArray(VAO);
    iCount > 0 ? 
        glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, 0)
	  : glDrawArrays(GL_TRIANGLES, 0, vCount);
    glBindVertexArray(0);
}

void Mesh::DrawInstanced(Shader& shader, int count) const
{
    // enable shader
    shader.use();

    // load colors
    shader.setVec3("material.ambient", material.ambient);
    shader.setVec3("material.diffuse", material.diffuse);
    shader.setVec3("material.specular", material.specular);
    shader.setFloat("material.shininess", material.shininess);

    // bind textures

    if (material.useDiffuseMap) {
        shader.setBool("material.useDiffuseMap", true);
        glActiveTexture(GL_TEXTURE1);
        shader.setInt("material.diffuseMap", 1);
        glBindTexture(GL_TEXTURE_2D, material.diffuseMaps[0].id);
    }
    else {
        shader.setBool("material.useDiffuseMap", false);
    }
    if (material.useSpecularMap)
    {
        shader.setBool("material.useSpecularMap", true);
        glActiveTexture(GL_TEXTURE2);
        shader.setInt("material.specularMap", 2);
        glBindTexture(GL_TEXTURE_2D, material.specularMaps[0].id);
    }
    else
    {
        shader.setBool("material.useSpecularMap", false);
    }

    glActiveTexture(GL_TEXTURE0);


    // draw mesh
    glBindVertexArray(VAO);
    iCount > 0 ?
        glDrawElementsInstanced(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, 0, count)
        : glDrawArraysInstanced(GL_TRIANGLES, 0, vCount, count);
    glBindVertexArray(0);
}

void Mesh::setupMesh() {
    GLCALL(glGenVertexArrays(1, &VAO));
    GLCALL(glBindVertexArray(VAO));

    GLCALL(glGenBuffers(1, &VBO));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, vCount * sizeof(vertex), vertices, GL_STATIC_DRAW));
    
    if (iCount > 0)
    {
        GLCALL(glGenBuffers(1, &EBO));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount * sizeof(unsigned int), indices, GL_STATIC_DRAW));
    }
    

    // vertex positions
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0));
    // vertex normals
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal)));
    // vertex texture coords
    GLCALL(glEnableVertexAttribArray(2));
    GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texCoords)));

    GLCALL(glBindVertexArray(0));
}


Texture::Texture(const char* path, const std::string& directory, std::string& typeName)
{
    this->type = typeName;
    this->path = std::string(path);
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    GLCALL(glGenTextures(1, &this->id));

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format(GL_RGB);
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        GLCALL(glBindTexture(GL_TEXTURE_2D, this->id));
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
        GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_image_free(data);
    }
    else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
}
