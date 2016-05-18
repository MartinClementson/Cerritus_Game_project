#pragma once

#include "../Source/LibIncluder.h"
#include "../Constants.h"
#include "../../LightStructs.h"
struct CbufferPerFrame
{
	DirectX::XMFLOAT4X4 camView;
	DirectX::XMFLOAT4X4 projection;
	DirectX::XMFLOAT4X4 invViewProjMatrix;
	DirectX::XMFLOAT4 worldPos;
	DirectX::XMFLOAT4 mousePos;
	int numPointLights = 0;
	int numSpotLights = 0;
	int numDirLights = 0;
	float pad;
};

//CamMatrices camMatrices;

struct WorldMatrix
{
	DirectX::XMFLOAT4X4 worldMatrix;
};
//WorldMatrix worldMatrix;

struct UV
{
	float enemyoffsetX;
	DirectX::XMFLOAT3 PaddingX;
	float waveoffsetX;
	DirectX::XMFLOAT3 PaddingY;
};



struct PointLightStruct
{
	PointLight	pointLights		[ MAX_NUM_POINTLIGHTS];
};

struct SpotLightStruct
{
	
	SpotLight	spotlights		[MAX_NUM_SPOTLIGHTS];

};

struct DirLightStruct
{
	
	DirectionalLight directionalLights[MAX_NUM_DIRLIGHTS];


};





struct SampleBoolStruct
{

	BOOL diffuseMap	 = FALSE	;
	BOOL normalMap	 = FALSE	;
	BOOL specularMap = FALSE	;
	BOOL glowMap	 = FALSE	;
};
