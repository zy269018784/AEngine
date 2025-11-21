#pragma once
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Model
{
public:
	void LoadModel(std::string const& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 mat1);
public:
    std::vector<float> VBOData;

	std::vector<unsigned int> EBOData;

	std::vector <std::string> Textures;
	//std::vector<int> offsets;
};