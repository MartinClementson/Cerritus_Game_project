#pragma once
#include "GameObject.h"
class Model :
	public GameObject
{
public:
	Model();
	~Model();
	void Initialize();
	void Release();
	void Update(double deltaTime);
	void Render();
private:
	//Meshes meshID; //enum
};

