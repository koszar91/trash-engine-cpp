#pragma once
#include "engine/entity/components/RigidBody.h"
#include "engine/entity/components/transform.h"
#include "engine/rendering/model/Model.h"


struct Entity
{
	Transform transform;

	Model *model;
	Shader* shader;
	RigidBody* rigid_body;

	Entity() = delete;
	Entity(Transform a_transform, Model* a_model, Shader* a_shader, RigidBody* a_rigid_body = nullptr);
	~Entity();

	void draw() const;
	
};

