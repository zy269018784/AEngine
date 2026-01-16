#pragma once
#include <string>
#include <vector>
#ifdef  PROJECT_USE_ASSIMP
	#include <assimp/Importer.hpp>
	#include <assimp/scene.h>
	#include <assimp/postprocess.h>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Model
{
public:
    Model();
	void LoadModel(std::string const& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 mat1);
public:
    std::vector<float> VBOData;

	std::vector<unsigned int> EBOData;

	std::vector<std::string> Textures;
	//std::vector<int> offsets;

    glm::vec3 AA;
    glm::vec3 BB;
    glm::vec3 Position;
    glm::vec3 LookAt;
    glm::vec3 Up;
    float Fov;
};
#endif