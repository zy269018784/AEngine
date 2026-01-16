#include "Model.h"
#include <list>
#include <iostream>
#ifdef  PROJECT_USE_ASSIMP

Model::Model()
{
    AA = glm::vec3(0, 0, 0);
    BB = glm::vec3(0, 0, 0);
}

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
    std::cout << "mNumCameras " << scene->mNumCameras << std::endl;
    if (scene->mNumCameras > 0) {
        Position.x = scene->mCameras[0]->mPosition.x;
        Position.y = scene->mCameras[0]->mPosition.y;
        Position.z = scene->mCameras[0]->mPosition.z;
        LookAt.x = scene->mCameras[0]->mLookAt.x;
        LookAt.y = scene->mCameras[0]->mLookAt.y;
        LookAt.z = scene->mCameras[0]->mLookAt.z;
        Up.x = scene->mCameras[0]->mUp.x;
        Up.y = scene->mCameras[0]->mUp.y;
        Up.z = scene->mCameras[0]->mUp.z;

        Fov = scene->mCameras[0]->mHorizontalFOV;

        std::cout << "Position "
                  << Position.x << " "
                  << Position.y << " "
                  << Position.z << " " << std::endl;


        std::cout << "LookAt "
                  << LookAt.x << " "
                  << LookAt.y << " "
                  << LookAt.z << " " << std::endl;

        std::cout << "Up "
                  << Up.x << " "
                  << Up.y << " "
                  << Up.z << " " << std::endl;
    }

    ProcessNode(scene->mRootNode, scene);

    std::cout << "AA " << AA.x << " " << AA.y << " "<< AA.z << std::endl;
    std::cout << "BB " << BB.x << " " << BB.y << " "<< BB.z << std::endl;
    std::cout << "Center " << (BB.x + AA.x) / 2.0 << " " << (BB.y + AA.y) / 2.0 << " "<< (BB.z + AA.z) / 2.0 << std::endl;
    std::cout << "Size " << (BB.x - AA.x)  << " " << (BB.y - AA.y) << " "<< (BB.z - AA.z)<< std::endl;
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
        if (p.x < AA.x)
            AA.x = p.x;
        if (p.y < AA.y)
            AA.y = p.y;
        if (p.z < AA.z)
            AA.z = p.z;

        if (p.x > BB.x)
            BB.x = p.x;
        if (p.y > BB.y)
            BB.y = p.y;
        if (p.z > BB.z)
            BB.z = p.z;

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
#endif
