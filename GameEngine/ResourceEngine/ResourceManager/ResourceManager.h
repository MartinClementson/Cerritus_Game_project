#pragma once
#include "../ResourceManager/MeshManager/MeshManager.h"
#include "../ResourceManager/ShaderManager/ShaderManager.h"
#include "../ResourceManager/BRFImporterHandler/BRFImporterHandler.h"
#include "../ResourceManager/MaterialManager/MaterialManager.h"
#include "../../Structs/RenderInfo.h"
class ResourceManager
{

private:
	RenderInstructions currentMesh;

	MaterialManager* materialManager		= nullptr;
	MeshManager* meshManager				= nullptr;
	ShaderManager* shaderManager			= nullptr;
	BRFImporterHandler* brfImporterHandler	= nullptr;

	bool gbufferPass						 = false;
	bool shadowPass							 = false;

public:
	ResourceManager();
	~ResourceManager();



	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();

	void SetGbufferPass(bool x);
	void SetShadowPass(bool x);

	RenderInstructions* GetRenderInfo(RenderInfoObject*		object);
	RenderInstructions* GetRenderInfo(RenderInfoUI*			object);
	RenderInstructions* GetRenderInfo(RenderInfoEnemy*		object);
	RenderInstructions* GetRenderInfo(RenderInfoChar*		object);
	RenderInstructions* GetRenderInfo(RenderInfoTrap*		object);
	
	RenderInstructions* GetPlaceHolderMesh(XMFLOAT3 position);
	RenderInstructions* GetPlaceHolderMesh(XMFLOAT3 position, XMFLOAT3 rotation);
	RenderInstructions* GetPlaceHolderPlane();
	RenderInstructions* GetFullScreenQuad();
	void SetShader(Shaders type) { this->shaderManager->SetActiveShader(type); };
private:
	XMFLOAT4X4 CalculateWorldMatrix(XMFLOAT3* position, XMFLOAT3* rotation);

	XMFLOAT4X4 CalculateWorldMatrix(XMFLOAT3* position, XMFLOAT3* rotation, XMFLOAT3* scale);
};

