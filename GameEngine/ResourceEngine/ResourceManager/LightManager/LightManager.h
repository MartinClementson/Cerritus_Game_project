#pragma once
#include "../../Structs/ConstantBufferStruct.h"


#define NUM_SPOTLIGHTS 2
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

	LightStruct lightStructure;

public:
	LightManager();
	~LightManager();
	void Initialize();
	void Release();

	int GetNumActivePointLights()	 {  return this->numActivePointLights; };
	int GetNumActiveSpotLights()	 {	return this->numActiveSpotLights;  };
	int GetNumActiveDirLights()		 {	return this->numActiveDirLights;   };
	LightStruct* GetLightStructure();
};

