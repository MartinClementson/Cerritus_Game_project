#pragma once
#include "../LibIncluder.h"
#include "../../Structs/ConstantBufferStruct.h"


#define NUM_SPOTLIGHTS 1
#define NUM_DIRLIGHTS	1
#define NUM_POINTLIGHTS 5
class LightManager
{

private:
	int numActivePointLights;
	int numActiveSpotLights;
	int numActiveDirLights;

	PointLight *		 pointLights	[MAX_NUM_POINTLIGHTS];
	DirectionalLight*	 dirLights		[ MAX_NUM_DIRLIGHTS	];
	SpotLight*			 spotLights		[ MAX_NUM_SPOTLIGHTS];

	PointLightStruct pointLightStruct;
	SpotLightStruct  spotLightStruct  ;
	DirLightStruct  dirLightStruct	  ;
	DirectX::XMFLOAT4 sunPosition = DirectX::XMFLOAT4(86.0f, 70.0f, 120.0f, 1.0f);

public:
	LightManager();
	~LightManager();
	void Initialize();
	void Release();

	int GetNumActivePointLights()	 {  return this->numActivePointLights; };
	int GetNumActiveSpotLights()	 {	return this->numActiveSpotLights;  };
	int GetNumActiveDirLights()		 {	return this->numActiveDirLights;   };
	void UpdateWorldLight(const DirectX::XMFLOAT3& position);
	PointLightStruct* GetPointLightStruct();
	SpotLightStruct*  GetSpotLightStruct();
	DirLightStruct*		GetDirLightStruct();
};

