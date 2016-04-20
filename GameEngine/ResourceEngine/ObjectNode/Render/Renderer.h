#pragma once

#pragma region Includes
#include "../../../Source/LibIncluder.h"
#include "../../../Source/Constants.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../Structs/DataTypes.h"
#include "../../ResourceManager/ResourceManager.h"
#include "..\Camera\Camera.h"
#include "../../../Structs/ConstantBufferStruct.h"

#pragma endregion


class Renderer
{

private:
	ID3D11DeviceContext* gDeviceContext	 = nullptr;
	ID3D11Device * gDevice			     = nullptr;
	ResourceManager* resourceManager	 = nullptr;

	Camera* sceneCam					 = nullptr;

	//Buffers
	ID3D11Buffer* worldBuffer			 = nullptr; //world constBuffer
	ID3D11Buffer* camBuffer				 = nullptr; //Camera constBuffer
	ID3D11Buffer* lightBuffer			 = nullptr; //Light constBuffer



public:
	Renderer();
	~Renderer();

	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();
	
	
	void Render(RenderInfoObject* object);
	void Render(RenderInfoUI* object);
	void Render(RenderInfoEnemy* object);
	void Render(RenderInfoChar* object);
	void Render(RenderInfoTrap* object);

	void RenderPlaceHolder();
	void RenderPlaceHolderPlane();
private:
	void Render(RenderInstructions* object);

	void UpdateCameraBuffer();
	void UpdateWorldBuffer(WorldMatrix* worldStruct);

	bool CreateConstantBuffers();

};
