#pragma once
#include <glm/vec2.hpp>

constexpr int SCR_WIDTH {1280};
constexpr int SCR_HEIGHT {720};
constexpr float START_MOUSE_SENSITIVITY {0.15f};
constexpr float START_CAMERA_SPEED{ 15.0f };

constexpr int CHUNK_SIZE{ 128 };

// terrain
constexpr int START_OCTAVES{ 5 };
constexpr float START_SCALE{ 0.014 };
constexpr float START_LACUNARITY{ 2.095 };
constexpr float START_PERSISTENCE{ 0.373 };
constexpr glm::vec2 START_OFFSET{ 0 };
constexpr glm::vec2 START_RES{ CHUNK_SIZE * 2 };
