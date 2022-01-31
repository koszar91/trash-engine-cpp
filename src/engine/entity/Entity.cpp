#include "Entity.h"

Entity::Entity(Transform a_transform, Model* a_model, Shader* a_shader, RigidBody* a_rigid_body)
	: transform(a_transform), model(a_model), shader(a_shader), rigid_body(a_rigid_body)
{

}

Entity::~Entity()
{
	if (rigid_body) delete(rigid_body);
}

void Entity::draw() const
{
	const glm::mat4 modelMatrix(transform.modelMatrix());
	shader->setMat4("model", modelMatrix);
	model->Draw(*shader);
}
