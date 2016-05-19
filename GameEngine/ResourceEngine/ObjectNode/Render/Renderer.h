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

#define LIGHTBUFFER_AMOUNT 3



enum LIGHTBUFFERS {
	BUFFER_POINTLIGHTS,
	BUFFER_SPOTLIGHTS,
	BUFFER_DIRLIGHTS
};

enum INSTANCED_BUFFERS
{
	INSTANCED_WORLD,
	BILLBOARD_BUFFER
};

class Renderer
{

private:

	int threadGroupsX = 32, threadGroupsY = 30; //This controls how many groups to dispatch in the compute shader. This value will be calculated att init to match the screen resolution

	ID3D11DeviceContext* gDeviceContext						= nullptr;
	ID3D11Device * gDevice									= nullptr;
	ResourceManager* resourceManager						= nullptr;

	Camera* sceneCam										= nullptr;

	//Buffers
	ID3D11Buffer* worldBuffer								= nullptr;	   //world constBuffer
	ID3D11Buffer* cbufferPerFrame							= nullptr;	   
	ID3D11Buffer* sampleBoolsBuffer							= nullptr;	   //samplingState constBuffer (Controls if a mesh has normalmap,specmap, etc)

	ID3D11Buffer* OffsetBuffer                              = nullptr; // the main idea of this buffer is to change the X coord for a specific texture, 
	
	ID3D11Buffer* instancedBuffers[UNIQUE_INSTANCED_BUFFER_AMOUNT] = { nullptr };

	LightManager lightmanager;
	ID3D11Buffer* lightBuffers[LIGHTBUFFER_AMOUNT]			= { nullptr }; //Light constBuffers


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
	float waveOffset = 0.028f;
	float enemyOffset = 0.056f;
public:
	Renderer();
	~Renderer();

	void Update(double deltaTime);

	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();
	
	void RenderBlurPass(ID3D11UnorderedAccessView* uav, ID3D11ShaderResourceView* srv);
	void RenderFinalPass();
	void SetGbufferPass(bool x) { this->resourceManager->SetGbufferPass(x); };
	void SetShadowPass(bool x) { this->resourceManager->SetShadowPass(x);  };
	void Render(RenderInfoObject* object);
	void Render(RenderInfoUI* object);
	void Render(RenderInfoEnemy* object);
	void Render(RenderInfoChar* object);
	void Render(RenderInfoTrap* object);
	void Render(std::vector<RenderInstructions>* object);

	void RenderInstanced(RenderInfoEnemy* object,  InstancedData* arrayData ,unsigned int amount);
	void RenderInstanced(RenderInfoObject* object, InstancedData* arrayData, unsigned int amount);
	void RenderInstanced(RenderInfoTrap* object,   InstancedData* arrayData, unsigned int amount);

	void RenderBillBoard(RenderInfoObject* object, BillboardData* arrayData, unsigned int amount);


	void RenderPlaceHolder(XMFLOAT3* position);
	void RenderPlaceHolder(XMFLOAT3* position, XMFLOAT3* rotation);
	void RenderPlaceHolderPlane();
	/*void RenderUIPass();*/

	void SetMouseWorldPos(XMFLOAT4 position);

	void GetInverseViewMatrix(XMMATRIX &matrix);
	void GetInverseProjectionMatrix(XMMATRIX &matrix);

	
	bool FrustumCheck(XMFLOAT3 pos, float radius);
	
private:
	void Render(RenderInstructions* object);
	void RenderQuadTree(RenderInstructions* object);
	void RenderInstanced(RenderInstructions* object, ID3D11Buffer* instanceBuffer, unsigned int amount);
	void RenderBillBoard(RenderInstructions* object, ID3D11Buffer* instanceBuffer, unsigned int amount);

	void MapLightBufferStructures();
	void UpdateCbufferPerFrame();
	void UpdateLightBuffer();
	void UpdateWorldBuffer(WorldMatrix* worldStruct);
	void UpdateSampleBoolsBuffer(SampleBoolStruct* sampleStruct);
	void updateUVBuffer(UV* uvstruct);
	bool CreateBuffers();
public:
	void UpdateCamera(XMFLOAT3 position) { this->sceneCam->UpdateView(position); this->UpdateCbufferPerFrame(); };
};
