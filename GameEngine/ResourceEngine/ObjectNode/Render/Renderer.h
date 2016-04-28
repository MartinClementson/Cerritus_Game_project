#pragma once

#pragma region Includes
#include "../../../Source/LibIncluder.h"
#include "../../../Source/Constants.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../Structs/DataTypes.h"
#include "../../ResourceManager/ResourceManager.h"
#include "..\Camera\Camera.h"
#include "../../../LightStructs.h"
#include "../../../Structs/ConstantBufferStruct.h"
#include "../../ResourceManager/LightManager/LightManager.h"


#pragma endregion
enum BUFFERS {
	BUFFER_POINTLIGHTS,
	BUFFER_SPOTLIGHTS,
	BUFFER_DIRLIGHTS
};

class Renderer
{

private:
	ID3D11DeviceContext* gDeviceContext						= nullptr;
	ID3D11Device * gDevice									= nullptr;
	ResourceManager* resourceManager						= nullptr;

	Camera* sceneCam										= nullptr;

	//Buffers
	ID3D11Buffer* worldBuffer								= nullptr; //world constBuffer
	ID3D11Buffer* cbufferPerFrame							= nullptr; 
	ID3D11Buffer* sampleBoolsBuffer							= nullptr; //samplingState constBuffer (Controls if a mesh has normalmap,specmap, etc)
	
	struct test {
		int i;
	};

	test testArray[2];
	ID3D11ShaderResourceView* testStructuredBufferSRV = nullptr;
	ID3D11Buffer*				testStructBuffer = nullptr;


	LightManager lightmanager;

	ID3D11Buffer* lightBuffers[3]							= { nullptr }; //Light constBuffers

	PointLightStruct* pointLightStruct						= nullptr;
	SpotLightStruct*  spotLightStruct						= nullptr;
	DirLightStruct*	  dirLightStruct						= nullptr;
	ID3D11ShaderResourceView* pointLightStructuredBuffer	= nullptr;
	ID3D11ShaderResourceView* spotLightStructuredBuffer		= nullptr;
	ID3D11ShaderResourceView* dirLightStructuredBuffer		= nullptr;

	XMFLOAT4 mouseWorldPos;

	int mNumPointLights = 0;
	int mNumSpotLights  = 0;
	int mNumDirLights	= 0;
public:
	Renderer();
	~Renderer();

	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();
	
	void RenderFinalPass();
	void SetGbufferPass(bool x) { this->resourceManager->SetGbufferPass(x); };
	void SetShadowPass(bool x) { this->resourceManager->SetShadowPass(x);  };
	void Render(RenderInfoObject* object);
	void Render(RenderInfoUI* object);
	void Render(RenderInfoEnemy* object);
	void Render(RenderInfoChar* object);
	void Render(RenderInfoTrap* object);

	void RenderPlaceHolder(XMFLOAT3* position);
	void RenderPlaceHolder(XMFLOAT3* position, XMFLOAT3* rotation);
	void RenderPlaceHolderPlane();


	void SetMouseWorldPos(XMFLOAT4 position);

	void GetInverseViewMatrix(XMMATRIX &matrix);
	void GetInverseProjectionMatrix(XMMATRIX &matrix);

	
private:
	void Render(RenderInstructions* object);
	void MapLightBufferStructures();
	void UpdateCbufferPerFrame();
	void UpdateLightBuffer();
	void UpdateWorldBuffer(WorldMatrix* worldStruct);
	void UpdateSampleBoolsBuffer(SampleBoolStruct* sampleStruct);
	bool CreateConstantBuffers();

};
