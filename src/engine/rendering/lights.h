#pragma once


#include <glm/gtx/transform.hpp>
#include "glm/glm.hpp"


struct DirectionalLight {
    glm::vec3 direction {0, 0, -1};

    glm::vec3 ambient {0.25f};
    glm::vec3 diffuse {0.95f};
    glm::vec3 specular {1.0f};
};

struct PointLight {
    glm::vec3 position {0.0f};

    glm::vec3 ambient {0.08f};
    glm::vec3 diffuse {0.9f};
    glm::vec3 specular {1.0f};

    // attenuation parameters
    float c {1.0f}, l {0.1f}, q {0.09f};
};

struct SpotLight {
    glm::vec3 position {};
    glm::vec3 direction {};

    glm::vec3 ambient {0.18f};
    glm::vec3 diffuse {0.9f};
    glm::vec3 specular {1.0f};

    // attenuation parameters
    float c {1.0f}, l {0.09f}, q {0.032f};

    float cosInner {cosf(glm::radians(12.5f))};
    float cosOuter {cosf(glm::radians(20.0f))};
};

