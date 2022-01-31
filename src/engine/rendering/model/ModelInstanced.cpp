#include "ModelInstanced.h"

ModelInstanced::ModelInstanced(std::vector<Mesh> a_meshes, std::vector<Transform> a_transforms)
	: Model(a_meshes), transforms(a_transforms)
{
	setupInstancedArray();
}

void ModelInstanced::Draw(Shader& a_shader) const
{
	for (auto& m : meshes) { m.DrawInstanced(a_shader, transforms.size()); }
}

void ModelInstanced::setTransforms(std::vector<Transform> a_transforms)
{
	this->transforms = a_transforms;
	setupInstancedArray();
}

std::vector<Transform> ModelInstanced::getTransforms() const
{
	return transforms;
}

std::vector<glm::mat4> ModelInstanced::getModelMatrices()
{
	std::vector<glm::mat4> matrices;
	for (auto& t : transforms)
	{
		matrices.push_back(t.modelMatrix());
	}
	return matrices;
}

void ModelInstanced::setupInstancedArray()
{
	const auto modelMatrices(getModelMatrices());

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(modelMatrices), &modelMatrices[0], GL_STATIC_DRAW);

	// set instance vertex attributes for each mesh
	for (const auto& mesh : meshes)
	{
		glBindVertexArray(mesh.VAO);

		const std::size_t vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
}
