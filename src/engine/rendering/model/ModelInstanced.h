#pragma once


#include "Model.h"
#include "engine/entity/components/transform.h"


class ModelInstanced : public Model
{
	unsigned int ibo;
	std::vector<Transform> transforms;

public:
	ModelInstanced(std::vector<Mesh> a_meshes,
		std::vector<Transform> a_transforms);

	void Draw(Shader& a_shader) const override;

	void setTransforms(std::vector<Transform> a_transforms);
	std::vector<Transform> getTransforms() const;

private:
	std::vector<glm::mat4> getModelMatrices();
	void setupInstancedArray();
};

