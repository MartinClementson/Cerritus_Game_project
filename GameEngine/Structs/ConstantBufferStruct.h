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

	DirectX::XMFLOAT4 lightPosition;
	DirectX::XMFLOAT4 lightColor;
	float intensity;
	DirectX::XMFLOAT3 pad;
};

