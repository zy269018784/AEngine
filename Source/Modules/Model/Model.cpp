#include "Model.h"
#include <list>


#include <iostream>

void Model::LoadModel(std::string const& path)
{
    Assimp::Importer importer;
   // const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

 //   const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    //std::cout << "mNumMeshes " << scene->mNumMeshes << std::endl;
    //std::cout << "mNumTextures " << scene->mNumTextures << std::endl;
    //for (int i = 0; i < scene->mNumTextures; i++)
    //{
    //    std::cout <<  scene->mTextures[i]->mFilename.C_Str() << std::endl;
    //}

    //for (int MaterialIndex = 0;  MaterialIndex < scene->mNumMaterials; MaterialIndex++)
    //{     
    //    unsigned int texture_count = scene->mMaterials[MaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE);
    //    std::cout << "MaterialIndex " << MaterialIndex  << " texture_count " << texture_count << std::endl;
    //    //for (int ProIndex = 0; ProIndex < scene->mMaterials[MaterialIndex]->mNumProperties; ProIndex++)
    //    //    std::cout << "MaterialIndex " << MaterialIndex  << " mProperties  " << ProIndex << " texture index " << scene->mMaterials[MaterialIndex]->mProperties[ProIndex]->mIndex << std::endl;;


    //}
    Textures.push_back("namaqualand_boulder_02_2k/textures/namaqualand_boulder_02_diff_2k.jpg");
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    aiNode* parent = node;
    std::list<aiMatrix4x4> mats;
    aiMatrix4x4 mat;
    while (parent) {
        mats.push_front(parent->mTransformation);
        parent = parent->mParent;
    }

    for (auto it = mats.begin(); it != mats.end(); it++) {
        mat *= *it;
    }
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene, mat);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {

        ProcessNode(node->mChildren[i], scene);
    }
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 mat1)
{
    std::cout << "name " << mesh->mName.C_Str() 
        << " mNumVertices " << mesh->mNumVertices
        << " IsIdentity " << mat1.IsIdentity()
        << std::endl;

    //float textureIndex = -1;
    //unsigned int texture_count = scene->mMaterials[mesh->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE);
    //if (texture_count > 0)
    //{
    //  //  scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE,);
    //}


    int offset = VBOData.size() / 3;        
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        auto p = mat1 * mesh->mVertices[i];
        VBOData.push_back(p.x);
        VBOData.push_back(p.y);
        VBOData.push_back(p.z);
        //if (0 == i)
        //{
        //    VBOData.push_back(0);
        //    VBOData.push_back(0);
        //}
        //else if (1 == i)
        //{
        //    VBOData.push_back(1);
        //    VBOData.push_back(0);
        //}
        //else if (2 == i)
        //{
        //    VBOData.push_back(1);
        //    VBOData.push_back(1);
        //}
        VBOData.push_back(mesh->mTextureCoords[0][i].x);
        VBOData.push_back(mesh->mTextureCoords[0][i].y); 

       // std::cout << mesh->mTextureCoords[0][i].x << " " << mesh->mTextureCoords[0][i].y << std::endl;
    }   
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            EBOData.push_back(offset + face.mIndices[j]);
    }
}
