#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include "stb_image.h"
#define MAX_BONE_INFLUENCE 4

using namespace std;
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
    
    static unsigned int LoadTexture(string path, string type)
    {
        unsigned int texture;
        glGenTextures(1, &texture);


        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            cout << "Failed to load texture" << endl;
        }
        stbi_image_free(data);

        return texture;
    }

};

struct VertexBoneData
{
    int BoneIDs[MAX_BONE_INFLUENCE] = { -1 };
    float Weights[MAX_BONE_INFLUENCE] = { 0.0f };
    int index = 0;  //次の添え字
 

    void AddBoneData(unsigned int BoneID, float Weight)
    {
        //　取得済みのボンドをスキップ
        for (int i = 0; i < index; i++)
        {
            if (BoneIDs[i] == BoneID)
            {
                return;

            }
        }
        
        if (Weight == 0.0f)
        {
            return;
        }

        if (index == MAX_BONE_INFLUENCE)
        {

            assert(0);
        }

        BoneIDs[index] = BoneID;
        Weights[index] = Weight;
        index++;
    }
};

//アニメーションなし用頂点
struct BasicVertex{
    // position
    glm::vec3 Position;
    // normal-
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;

};

//skinmesh animetion用頂点
struct Vertex :public BasicVertex
{
    // tangent
    glm::vec3 Tangent;
    // bitangent
    //glm::vec3 Bitangent;

    VertexBoneData BoneData;
    Vertex();
    Vertex(glm::vec3&&, glm::vec3&&, glm::vec2&&, glm::vec3&&);
};


#endif