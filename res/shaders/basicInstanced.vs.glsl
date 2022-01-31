#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in mat4 instanceModelMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    FragPos = vec3(instanceModelMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(instanceModelMatrix))) * aNormal; // apply model transform to a normal
    TexCoords = aTexCoords;

    gl_Position = proj * view * instanceModelMatrix * vec4(aPos, 1.0);
}