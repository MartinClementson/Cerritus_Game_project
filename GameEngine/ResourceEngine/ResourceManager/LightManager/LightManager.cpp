#include "LightManager.h"



LightManager::LightManager()
{

	numActivePointLights	= 0;
	numActiveSpotLights		= 0;
	numActiveDirLights		= 0;
	for (size_t i = 0; i < MAX_NUM_POINTLIGHTS; i++)
		pointLights[i] = nullptr;

	for (size_t i = 0; i < MAX_NUM_SPOTLIGHTS; i++)
		spotLights[i] = nullptr;

	for (size_t i = 0; i < MAX_NUM_DIRLIGHTS; i++)
		dirLights[i] = nullptr;

}


LightManager::~LightManager()
{

	for (size_t i = 0; i < NUM_POINTLIGHTS; i++)
	{

		delete pointLights[i];
	}
}

void LightManager::Initialize()
{
	for (size_t i = 0; i < NUM_POINTLIGHTS; i++)
	{
		this->pointLights[i] = new PointLight();
		pointLights[i]->lightPosition = DirectX::XMFLOAT4(0.0f, 30.0f, 0.0f, 1.0f); //Pos
		pointLights[i]->lightLookAt = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);	//Direct
		pointLights[i]->lightDiffuse = DirectX::XMFLOAT4(3.0f, 1.0f, 5.0f, 1.0f);	//Color
		pointLights[i]->SetMatrices(DirectX::XM_PI*0.8f, 1.0f, 5.0f, 40.0f);
		pointLights[i]->intensity = 1.0f;
		this->numActivePointLights += 1;

	}

}
void LightManager::Release()			  

{
}

PointLightStruct * LightManager::GetPointLightStruct()
{

	for (size_t i = 0; i < numActivePointLights; i++)
		pointLightStruct.pointLights[i] = *pointLights[i];
	return &pointLightStruct;
}

SpotLightStruct * LightManager::GetSpotLightStruct()
{
	
		for (size_t i = 0; i < numActiveSpotLights; i++)
			spotLightStruct.spotlights[i] = *spotLights[i];

	return &spotLightStruct;
}

DirLightStruct * LightManager::GetDirLightStruct()
{
	for (size_t i = 0; i < numActiveDirLights; i++)
		dirLightStruct.directionalLights[i] = *dirLights[i];

	return &dirLightStruct;
}
