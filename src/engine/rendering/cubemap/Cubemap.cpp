#include "Cubemap.h"

#include "stb_image.h"
#include "engine/rendering/gl_utils.h"


const std::string Cubemap::cubemapsPath = "res/textures/cubemaps";

const std::vector<std::string> Cubemap::faces = {
    // "right.png",
    // "left.png",
    // "top.png",
    // "bottom.png",
    // "front.png",
    // "back.png"
	"right.jpg",
    "left.jpg",
    "top.jpg",
    "bottom.jpg",
    "front.jpg",
    "back.jpg"
};


Cubemap::Cubemap(std::string name) : name(name), verticesData{
    // sorry XD dunno where to put it
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
}

{
    // init vertex data
    GLCALL(glGenVertexArrays(1, &VAO));
    GLCALL(glGenBuffers(1, &VBO));
    GLCALL(glBindVertexArray(VAO));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), &verticesData, GL_STATIC_DRAW));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    // init textures
    GLCALL(glGenTextures(1, &textureID));
    GLCALL(glActiveTexture(GL_TEXTURE0));
    GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));
    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        std::string path = cubemapsPath + "/" + name + "/" + faces[i];
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if (!data)
        {
            std::cout << "Error: cannot find file '" << path << "'."
        			  << "Cubemap loading failed." << std::endl;
            stbi_image_free(data);
        	exit(1);
        }
    	
        GLenum format(GL_RGB);
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
        stbi_image_free(data);
        

    }
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

}

void Cubemap::Draw(Shader& shader) const
{
    GLCALL(glBindVertexArray(VAO));
    GLCALL(glActiveTexture(GL_TEXTURE0));
    GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));
    GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
    GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}
