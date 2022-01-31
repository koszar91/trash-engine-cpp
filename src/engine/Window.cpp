#include <GL/glew.h>
#include "Window.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "stb_image.h"
#include "key_listeners/MouseListener.h"
#include "key_listeners/KeyListener.h"
#include "scene/RacingScene.h"
#include "scene/TerrainGenerationScene.h"


Window Window::_instance;


Window::Window()
{
    // initialize window / GLFW
    if (!glfwInit()) {
        printf("Could not initialize GLFW.");
        exit(1);
    }

    // configure GLFW
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(_window);


    // init OpenGL
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        std::cout << "GLEW intialization failed." << std::endl;
        exit(1);
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


    // setup ImGui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(_window, true);
    ImGui::StyleColorsDark();

    

    // enable v-sync
    glfwSwapInterval(0);

    glfwShowWindow(_window);

    glEnable(GL_DEPTH_TEST);
    
}


Window& Window::get()
{
	return _instance;
}

void Window::run()
{
    setScene(TERRAIN_GEN_SCENE);

    double start(0), dt(0.0f);
    while (!glfwWindowShouldClose(get()._window))
    {
        
        setCallbacks();
        glfwPollEvents();
        unsetCallbacks();
        ImGui_ImplGlfwGL3_NewFrame();

        updateFPS();

        get().currentScene->update(dt);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        get().currentScene->render(dt);

        get().currentScene->updateImGui(dt);

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(get()._window);

        MouseListener::frameEnded();

        double end = glfwGetTime();
        dt = end - start;
        get().FPS = 1 / dt;
        start = glfwGetTime();
    }

    delete(get().currentScene);

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(get()._window);
    glfwTerminate();
}

void Window::setScene(int scene)
{
    switch(scene)
    {
    case TERRAIN_GEN_SCENE: get().currentScene = new TerrainGenerationScene(); break;
    case RACING_SCENE: get().currentScene = new RacingScene(); break;
    default: std::cout << "Cannot change scene to '" << scene << "', it is unknown." << std::endl; break;
    }
}

void Window::close()
{
    glfwSetWindowShouldClose(get()._window, true);
}

GLFWwindow* Window::getWindow()
{
    return get()._window;
}

void Window::setClearColor(glm::vec3 color)
{
    glClearColor(color.r, color.g, color.b, 1.0f);
}


void Window::switchCursorActive() {
    if (get()._isCursorActive) {
        setCursorInactive();
        get()._isCursorActive = false;
    }
    else {
        setCursorActive();
        get()._isCursorActive = true;
    }
}

void Window::setCursorActive() {
    glfwSetInputMode(get()._window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    get()._isCursorActive = true;
}

void Window::setCursorInactive() {
    glfwSetInputMode(get()._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    get()._isCursorActive = false;
}

void Window::setCallbacks()
{
    glfwSetCursorPosCallback(get()._window, MouseListener::mousePositionCallback);
    glfwSetMouseButtonCallback(get()._window, MouseListener::mouseButtonCallback);
    glfwSetScrollCallback(get()._window, MouseListener::mouseScrollCallback);
    glfwSetKeyCallback(get()._window, KeyListener::keyCallback);
}

void Window::unsetCallbacks()
{
    glfwSetCursorPosCallback(get()._window, nullptr);
    glfwSetMouseButtonCallback(get()._window, nullptr);
    glfwSetScrollCallback(get()._window, nullptr);
    glfwSetKeyCallback(get()._window, nullptr);
}

void Window::updateFPS()
{
    float now = glfwGetTime();

    float elapsed = now - get().lastFPSUpdate;
    if (elapsed > get().refreshFPSPeriod && get().FPS != 0)
    {
        get().lastFPSUpdate = glfwGetTime();
        glfwSetWindowTitle(get()._window, (get()._title + " | " + std::to_string(get().FPS) + " fps").c_str());
    }

}

