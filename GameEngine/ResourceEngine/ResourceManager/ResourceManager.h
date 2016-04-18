#pragma once
#include "../ResourceManager/MeshManager/MeshManager.h"
#include "../ResourceManager/ShaderManager/ShaderManager.h"
#include "../../Structs/RenderInfo.h"
class ResourceManager
{

private:
	RenderInstructions currentMesh;

	MeshManager* meshManager		= nullptr;
	ShaderManager* shaderManager	= nullptr;
public:
	ResourceManager();
	~ResourceManager();



	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();


RenderInstructions* GetRenderInfo(RenderInfoObject*		object);
RenderInstructions* GetRenderInfo(RenderInfoUI*			object);
RenderInstructions* GetRenderInfo(RenderInfoEnemy*		object);
RenderInstructions* GetRenderInfo(RenderInfoChar*		object);
RenderInstructions* GetRenderInfo(RenderInfoTrap*		object);

RenderInstructions* GetPlaceHolderMesh();
};
