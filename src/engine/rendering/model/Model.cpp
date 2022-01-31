#include "Model.h"

Model::Model(std::vector<Mesh> meshes) : meshes(meshes)
{

}

void Model::Draw(Shader &shader) const {
    for (auto mesh : meshes) { mesh.Draw(shader); }
}