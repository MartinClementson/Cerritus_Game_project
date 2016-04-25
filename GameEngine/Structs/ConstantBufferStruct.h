#pragma once

#include "../Source/LibIncluder.h"

struct CamMatrices
{
	DirectX::XMFLOAT4X4 camView;
	DirectX::XMFLOAT4X4 projection;
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

};


struct SampleBoolStruct
{

	BOOL diffuseMap	 = FALSE	;
	BOOL normalMap	 = FALSE	;
	BOOL specularMap = FALSE	;
	BOOL glowMap	 = FALSE	;
};
