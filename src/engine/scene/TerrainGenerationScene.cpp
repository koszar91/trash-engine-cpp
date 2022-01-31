#include "TerrainGenerationScene.h"

#include <random>
#include "imgui.h"
#include "engine/rendering/gl_utils.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>
#include "glm/glm.hpp"
#include "engine/Window.h"
#include "engine/key_listeners/KeyListener.h"
#include "engine/key_listeners/MouseListener.h"


TerrainGenerationScene::TerrainGenerationScene()
{

    // setup window properties for this scene
    Window::setCursorInactive();
    Window::setClearColor(glm::vec3(0.6f, 0.6f, 0.8f));

    camera = Camera{ glm::vec3(0, terrainHeightMap.hMax, 0) };
    glm::mat4 view = camera.getViewMatrix();

    // initialize shaders' uniforms that does not change (too often)
    basicShader.use();
    basicShader.setVec3("dirLight.direction", glm::vec3(-0.5, -1, -1));
    basicShader.setVec3("dirLight.ambient", glm::vec3(0.25));
    basicShader.setVec3("dirLight.diffuse", glm::vec3(0.95));
    basicShader.setVec3("dirLight.specular", glm::vec3(1));
    basicShader.setMat4("proj", proj);
    basicShader.setMat4("view", view);

}

TerrainGenerationScene::~TerrainGenerationScene()
{
    delete(trees);
}


std::vector<Transform> TerrainGenerationScene::genTreesTransforms(int count)
{
    std::vector<Transform> transforms;

    std::default_random_engine engine(1);
    std::uniform_real_distribution distrib(0.0f, 1.0f - FLT_EPSILON);

    for (int i = 0; i < count; i++)
    {
        float x = distrib(engine);
        float z = distrib(engine);
        float y = 0.5 + terrainHeightMap.sample(x, z);
        float rot = distrib(engine) * 2.0f * (float) AI_MATH_PI;


        Transform transform(glm::vec3((x - 0.5f) * CHUNK_SIZE, y, (z - 0.5f) * CHUNK_SIZE),
							glm::vec3(0.0f, rot, 0.0f),
							glm::vec3(0.2f));

        transforms.emplace_back(transform);
    }

    return transforms;
}

void TerrainGenerationScene::update(float dt)
{
    trees = new Entity(Transform(), &instancedTreesModel, &basicInstancedShader);

    // escape key to close application
    if (KeyListener::isKeyPressed(GLFW_KEY_ESCAPE))
        Window::close();

    // update looking direction based on mouse
    if (isCameraActive) updateCameraBasedOnMouse(dt);

    // c to switch cursor
    if (KeyListener::isKeyPressed(GLFW_KEY_C))
    {
        Window::switchCursorActive();
        isCameraActive ? isCameraActive = false : isCameraActive = true;
    }
}

void TerrainGenerationScene::render(float dt)
{
	const glm::mat4 view = camera.getViewMatrix();

    // draw entities
    basicShader.use();
    basicShader.setMat4("view", view);
    basicShader.setVec3("viewPos", camera.getPosition());
    terrain.draw();
    trees->draw();
}

void TerrainGenerationScene::updateImGui(float dt)
{
    
    ImGui::Begin("View info");
    const auto camPos = camera.getPosition();
    const auto frontDir = camera.getFront();
    ImGui::Text("Position: %f2, %f2, %f2", camPos.x, camPos.y, camPos.z);
    ImGui::Text("Front: %f2, %f2, %f2", frontDir.x, frontDir.y, frontDir.z);
    ImGui::End();

    ImGui::Begin("Settings");
    ImGui::InputFloat("Move speed ", &cameraMoveSpeed);
    ImGui::InputFloat("Look speed ", &mouseSensitivity);
    ImGui::End();

    int oct{octaves};
    float sc{ scale }, lac{ lacunarity }, pers{persistence};
    glm::vec2 res{ mapRes }, offs{ mapOffset };
    ImGui::Begin("Terrain mods");
    ImGui::SliderInt("Octaves", &oct, 1, 10);
    ImGui::SliderFloat("Scale", &sc, 1e-4, 1e-1);
    ImGui::SliderFloat("Lacunarity", &lac, 1 + FLT_EPSILON, 5);
    ImGui::SliderFloat("Persistence", &pers, FLT_EPSILON, 5);
    ImGui::SliderFloat2("Offset", &offs.x, -10, 10);
    // ImGui::SliderFloat2("Res", &res.x, 10, 1000);
	ImGui::End();

    if (oct != octaves ||
        sc != scale ||
        lac != lacunarity ||
        pers != persistence ||
        res != mapRes ||
        offs != mapOffset)
    {
        terrainHeightMap = HeightMapGenerator::genPerlin(offs, res, oct, sc, lac, pers);
        terrainModel = mb.buildFromHeightMap(CHUNK_SIZE, CHUNK_SIZE, terrainHeightMap);
        terrain = Entity(Transform(), &terrainModel, &basicShader);
    
    	octaves = oct;
        scale = sc;
        lacunarity = lac;
        persistence = pers;
        mapOffset = offs;
        mapRes = res;
    }

}


