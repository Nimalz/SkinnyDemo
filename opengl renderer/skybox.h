#pragma once
#include "cubemap.h"
#include "gameobject.h"
#include "shader.h"
#include "camera.h"

class Skybox:public GameObject
{
public:
	unsigned int VAO;
private:
	unsigned int VBO;
	vector<unique_ptr<Cubemap>> m_Texture;

public:
	Skybox();
	~Skybox() = default;
	void Clear();
	void LoadTexture(vector<std::string> faces);
	void DrawSkybox(Shader&,Camera&);
};
