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

	for (size_t i = 0; i < NUM_DIRLIGHTS; i++)
	{

		delete dirLights[i];
	}

	for (size_t i = 0; i < NUM_SPOTLIGHTS; i++)
	{

		delete spotLights[i];
	}
}

void LightManager::Initialize()
{
	//for (size_t i = 0; i < NUM_POINTLIGHTS; i++)
	//{
	//	this->pointLights[i] = new PointLight();
	//	pointLights[i]->lightPosition = DirectX::XMFLOAT4(0.0f, 30.0f, 0.0f, 1.0f); //Pos
	//	pointLights[i]->lightLookAt = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);	//Direct
	//	pointLights[i]->lightDiffuse = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);	//Color
	//	pointLights[i]->SetMatrices(DirectX::XM_PI*0.8f, 1.0f, 5.0f, 40.0f);
	//	pointLights[i]->intensity = 1.0f;
	//	this->numActivePointLights += 1;

	//}

#pragma region Temp lights

	this->pointLights[0] = new PointLight();
	pointLights[0]->lightPosition = DirectX::XMFLOAT4(0.0f, 40.0f, 0.0f, 1.0f); //Pos
	pointLights[0]->lightLookAt = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);	//Direct
	pointLights[0]->lightDiffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	//Color
	pointLights[0]->SetMatrices(DirectX::XM_PI*0.8f, 1.0f, 1.0f, 100.0f);
	pointLights[0]->castShadow = FALSE;
	pointLights[0]->intensity = 4.0f;
	pointLights[0]->lightRange = 5000.0f;
	
	this->numActivePointLights += 1;


	//this->pointLights[1] = new PointLight();
	//pointLights[1]->lightPosition = DirectX::XMFLOAT4(0.0f, 20.0f, 30.0f, 1.0f); //Pos
	//pointLights[1]->lightLookAt = DirectX::XMFLOAT4(0.0f, -10.0f, 28.0f, 1.0f);	//Direct
	//pointLights[1]->lightDiffuse = DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);	//Color
	//pointLights[1]->SetMatrices(DirectX::XM_PI*0.8f, 1.0f, 1.0f, 100.0f);
	//pointLights[1]->intensity = 4.0f;
	//pointLights[1]->castShadow = FALSE;
	//pointLights[1]->lightRange = 50.0f;
	//	this->numActivePointLights += 1;	



	//this->pointLights[2] = new PointLight();
	//pointLights[2]->lightPosition = DirectX::XMFLOAT4(0.0f, 20.0f, -30.0f, 1.0f); //Pos
	//pointLights[2]->lightLookAt = DirectX::XMFLOAT4(0.0f, -10.0f, 28.0f, 1.0f);	//Direct
	//pointLights[2]->lightDiffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	//Color
	//pointLights[2]->SetMatrices(DirectX::XM_PI*0.8f, 1.0f, 1.0f, 100.0f);
	//pointLights[2]->intensity = 4.0f;
	//pointLights[2]->castShadow = FALSE;
	//pointLights[2]->lightRange = 50.0f;
	//this->numActivePointLights += 1;


	//this->pointLights[3] = new PointLight();
	//pointLights[3]->lightPosition = DirectX::XMFLOAT4(40.0f, 20.0f, 0.0f, 1.0f); //Pos
	//pointLights[3]->lightLookAt = DirectX::XMFLOAT4(0.0f, -10.0f, 28.0f, 1.0f);	//Direct
	//pointLights[3]->lightDiffuse = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);	//Color
	//pointLights[3]->SetMatrices(DirectX::XM_PI*0.8f, 1.0f, 1.0f, 100.0f);
	//pointLights[3]->intensity = 8.0f;
	//pointLights[3]->castShadow = FALSE;
	//pointLights[3]->lightRange = 50.0f;
	//this->numActivePointLights += 1;


	//this->pointLights[4] = new PointLight();
	//pointLights[4]->lightPosition = DirectX::XMFLOAT4(00.0f, 20.0f, -60.0f, 1.0f); //Pos
	//pointLights[4]->lightLookAt = DirectX::XMFLOAT4(0.0f, -10.0f, 28.0f, 1.0f);	//Direct
	//pointLights[4]->lightDiffuse = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);	//Color
	//pointLights[4]->SetMatrices(DirectX::XM_PI*0.8f, 1.0f, 1.0f, 100.0f);
	//pointLights[4]->intensity = 4.0f;
	//pointLights[4]->castShadow = FALSE;
	//pointLights[4]->lightRange = 50.0f;
	//this->numActivePointLights += 1;



	pointLights[0]->attenuation = 0.002f;
	/*pointLights[1]->attenuation = 0.02;
	pointLights[2]->attenuation = 0.02;
	pointLights[4]->attenuation = 0.02;
	pointLights[3]->attenuation = 0.02;*/

	this->dirLights[0] = new DirectionalLight();
	this->dirLights[0]->lightPosition = DirectX::XMFLOAT4(30.0f, 40.0f, 0.0f,1.0f);
	this->dirLights[0]->lightDiffuse  = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	this->dirLights[0]->lightLookAt = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);	//Direct
	this->dirLights[0]->intensity = 6.0;
	this->dirLights[0]->SetMatrices(1.0f, 0.0f, 120.0f);
	this->dirLights[0]->castShadow = TRUE;
	numActiveDirLights +=1;
#pragma endregion


}
void LightManager::Release()			  

{
}

PointLightStruct * LightManager::GetPointLightStruct()
{
	static float z = 5.5f;						 //TEMPORARY
	static float x = 5.5f;						 //TEMPORARY
	for (size_t i = 0; i < numActivePointLights; i++)
	{
		//pointLights[i]->lightPosition.z = 60; //TEMPORARY
		//pointLights[i]->lightPosition.x = +z;
		pointLightStruct.pointLights[i] = *pointLights[i];
		//x +=  (float) cos(z)* 0.006f * i;					 //TEMPORARY
		//z +=  (float)sin(x)* 0.06f * i;					 //TEMPORARY
	}
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
