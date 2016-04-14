#pragma once
#include "MeshManager.h"
#include "ShaderManager.h"
#include "RenderInfo.h"
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


RenderInstructions* GetRenderInfo(RenderInfoObject*		object);
RenderInstructions* GetRenderInfo(RenderInfoUI*			object);
RenderInstructions* GetRenderInfo(RenderInfoEnemy*		object);
RenderInstructions* GetRenderInfo(RenderInfoChar*		object);
RenderInstructions* GetRenderInfo(RenderInfoTrap*		object);
};

