#include "RacingScene.h"

#include <glm/ext/matrix_transform.hpp>

#include "imgui.h"
#include "engine/Window.h"
#include "engine/key_listeners/KeyListener.h"
#include "engine/key_listeners/MouseListener.h"

RacingScene::RacingScene()
{
	// setup window properties for this scene
	Window::setCursorActive();
	Window::setClearColor(glm::vec3(0.6f, 0.6f, 0.8f));

	// initialize shaders' uniforms that does not change (too often)
	const glm::mat4 view = camera.getViewMatrix();
	basicShader.use();
	basicShader.setVec3("dirLight.direction", glm::vec3(-0.5, -1, -1));
	basicShader.setVec3("dirLight.ambient", glm::vec3(0.25));
	basicShader.setVec3("dirLight.diffuse", glm::vec3(0.95));
	basicShader.setVec3("dirLight.specular", glm::vec3(1));
	basicShader.setMat4("proj", proj);
	basicShader.setMat4("view", view);

	// nice position for static camera to look at the map from an angle
	// camera.setPosition(glm::vec3(80, 23, 35));
	// camera.setFront(glm::vec3(-0.75, -0.44, -0.48));

	// set camera behind the car
	camera.setPosition(car.transform.position - (car.transform.orientation() * 7.0f) + glm::vec3(0, 3.3, 0));
	camera.setFront(car.transform.orientation() - glm::vec3(0, 0.15, 0));

	car.transform.position.y += 1;

	isCameraActive = true;
}

RacingScene::~RacingScene()
{
}

void RacingScene::update(float dt)
{
	carSystem.update(car, dt);

	updateCameraToFollowCar(1, car.transform.position, car.transform.orientation(), dt);

	// escape key to close application
	if (KeyListener::isKeyPressed(GLFW_KEY_ESCAPE)) Window::close();
}


void RacingScene::render(float dt)
{
	const glm::mat4 view = camera.getViewMatrix();

	// draw entities
	basicShader.use();
	basicShader.setMat4("view", view);
	basicShader.setVec3("viewPos", camera.getPosition());
	track.draw();
	car.draw();
}

void RacingScene::updateImGui(float dt)
{
	{
		ImGui::Begin("View info");
		const auto camPos = camera.getPosition();
		const auto frontDir = camera.getFront();
		ImGui::Text("Position: %f2, %f2, %f2", camPos.x, camPos.y, camPos.z);
		ImGui::Text("Front: %f2, %f2, %f2", frontDir.x, frontDir.y, frontDir.z);
		ImGui::End();
	}


	{
		ImGui::Begin("Car info");

		const glm::vec3 orientation(car.transform.orientation());
		const glm::vec3 position(car.transform.position);

		ImGui::Text("TRANSLATIONAL");
		ImGui::Text("position   : %.1f, %.1f, %.1f", position.x, position.y, position.z);
		ImGui::Text("velocity   : %.1f, %.1f, %.1f", car.rigid_body->velocity.x, car.rigid_body->velocity.y,
		            car.rigid_body->velocity.z);
		ImGui::Text("net force  : %.1f, %.1f, %.1f", car.rigid_body->net_force.x, car.rigid_body->net_force.y,
		            car.rigid_body->net_force.z);
		ImGui::Text("speed   : %.1f", length(car.rigid_body->velocity));
		ImGui::Text("mass    : %.1f", car.rigid_body->mass);

		ImGui::Text("\nROTATIONAL");
		ImGui::Text("orientation: %.1f, %.1f, %.1f", orientation.x, orientation.y, orientation.z);
		ImGui::Text("velocity   : %.1f, %.1f, %.1f", car.rigid_body->angular_velocity.x,
		            car.rigid_body->angular_velocity.y, car.rigid_body->angular_velocity.z);
		ImGui::Text("net torque : %.1f, %.1f, %.1f", car.rigid_body->net_torque.x, car.rigid_body->net_torque.y,
		            car.rigid_body->net_torque.z);
		ImGui::Text("speed   : %.1f", glm::length(car.rigid_body->angular_speed()));
		ImGui::Text("inertia : %.1f", car.rigid_body->inertia);

		ImGui::End();
	}

	{
		ImGui::Begin("Track info");

		const glm::vec3 orientation(track.transform.orientation());
		const glm::vec3 position(track.transform.position);
		ImGui::Text("Position   : %.1f, %.1f, %.1f", position.x, position.y, position.z);
		ImGui::Text("Orientation: %.1f, %.1f, %.1f", orientation.x, orientation.y, orientation.z);

		ImGui::End();
	}

}


void RacingScene::updateCameraToFollowCar(int mode, glm::vec3 carPosition, glm::vec3 carOrientation, float dt)
{

	float posCoeff = 2.7f;
	float orientCoeff = 1.7f;

	glm::vec3 currCamPosition = camera.getPosition();
	glm::vec3 currCamOrientation = camera.getFront();

	glm::vec3 tagetCamPosition = carPosition - (carOrientation * 7.0f) + glm::vec3(0, 3.3, 0);
	glm::vec3 targetCamOrientation = carOrientation - glm::vec3(0, 0.15, 0);

	glm::vec3 resultCamPosition;
	glm::vec3 resultCamOrientation;

	switch (mode)
	{
	case 0: // stiff movement, like on a stick
		{
			resultCamPosition = tagetCamPosition;
			resultCamOrientation = targetCamOrientation;
			break;
		}


	case 1: // lerped, smooth movement
		{
			resultCamPosition = currCamPosition + (tagetCamPosition - currCamPosition) * posCoeff * dt;
			resultCamOrientation = currCamOrientation + (targetCamOrientation - currCamOrientation) * orientCoeff * dt;
			break;
		}
	}

	camera.setPosition(resultCamPosition);
	camera.setFront(resultCamOrientation);
}
