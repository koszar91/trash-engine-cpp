#version 330 core

layout(location = 0) in vec3 aPos;
uniform mat4 proj;
uniform mat4 view;

out vec3 fTexCoords;

void main() {
	fTexCoords = aPos;

	gl_Position = proj * view * vec4(aPos, 1.0);
	
	// vec4 pos = proj * view * vec4(aPos, 1.0);
	// gl_Position = pos.xyww;
}