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
}

void LightManager::Initialize()
{
	

}

void LightManager::Release()
{
}

LightStruct * LightManager::GetLightStructure()
{

	for (size_t i = 0; i < numActiveSpotLights; i++)
		lightStructure.spotlights[i] = *spotLights[i];
	
	for (size_t i = 0; i < numActivePointLights; i++)
		lightStructure.pointLights[i] = *pointLights[i];

	for (size_t i = 0; i < numActiveDirLights; i++)
		lightStructure.directionalLights[i] = *dirLights[i];
	

	



	return &lightStructure;
}
