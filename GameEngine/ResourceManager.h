#pragma once
#include "MeshManager.h"
#include "ShaderManager.h"
class ResourceManager
{

private:
	MeshManager* meshManager		= nullptr;
	ShaderManager* shaderManager	= nullptr;
public:
	ResourceManager();
	~ResourceManager();



	void Initialize();
	void Release();
};

