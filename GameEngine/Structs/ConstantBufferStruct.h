#pragma once

#include "../Source/LibIncluder.h"
#include "../Constants.h"
#include "../../LightStructs.h"
struct CamMatrices
{
	DirectX::XMFLOAT4X4 camView;
	DirectX::XMFLOAT4X4 projection;
	DirectX::XMFLOAT4X4 invViewProjMatrix;
	DirectX::XMFLOAT4 worldPos;
	DirectX::XMFLOAT4 mousePos;
};
//CamMatrices camMatrices;

struct WorldMatrix
{
	DirectX::XMFLOAT4X4 worldMatrix;
};
//WorldMatrix worldMatrix;


struct LightStruct
{
	PointLight		 pointLights		[ MAX_NUM_POINTLIGHTS];
	DirectionalLight directionalLights	[ MAX_NUM_DIRLIGHTS  ];
	SpotLight		 spotlights			[ MAX_NUM_SPOTLIGHTS ];

};



struct SampleBoolStruct
{

	BOOL diffuseMap	 = FALSE	;
	BOOL normalMap	 = FALSE	;
	BOOL specularMap = FALSE	;
	BOOL glowMap	 = FALSE	;
};
