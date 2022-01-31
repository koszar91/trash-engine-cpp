#pragma once


#include <vector>
#include "Mesh.h"


class Model {

protected:
    std::vector<Mesh> meshes;

public:

    Model(std::vector<Mesh> meshes);
    virtual ~Model() = default;

    virtual void Draw(Shader &shader) const;
};

