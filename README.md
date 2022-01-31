# Trash-Engine
My first attempt to build my own 3D engine for games using C++.
I suspended developing this project, to rewrite it in Java

# Tech
Project is written in C++.
It uses OpenGL for GPU communication. It also uses custom build GLSL shaders.
Assimp library is used to dynamically load 3D models in obj format.
GLFW is used for window creation and management and user interaction as well.

# Scenes
I created two interactive scenes.

Terrain Generation Scene contains a procedurally generated terrain. The geometry is computed using Perlin Noise algorithm.
For movement the WASD, Space and Shift keys are used.
It also contains simple GUI to modify the Perlin Noise parameters, which are dynamically recalculated and displayed when user changes it.

Car Racing Scene is my attempt to implement car dynamics.
User can steer the car using WASD and Space keys.
I've done some physics research to figure out how to implement the car dynamics.
Process ivolves some geometric computations with car tires to find steering forces acting on a car.
Engine, braking and friction forces also influence the car movement.
After all forces and torques are computed, the numerical integration (over time dt) is performed.

# Further plans
I'm going to rewrite the entire project to Java.
When I'm done, I'm planning to learn and implement these features (and more):
- full 3D collision system
- full 3D physics system
- animations of models
- some graphics features like reflection, refraction
- instancing (very useful technique of drawing multiple objects allowing a significant speed boost when rendering)
- ray tracing
- basically everything i find interesting

# Usage
Project was entirely written in Visual Studio 2019, so for usage just download VS, build and run it (I hope).
