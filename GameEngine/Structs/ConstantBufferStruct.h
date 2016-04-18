#pragma once

#include "../Source/LibIncluder.h"

struct CamMatrices
{
	DirectX::XMMATRIX camView;
	DirectX::XMMATRIX projection;
	DirectX::XMFLOAT3 worldPos;
	float padding;
};
//CamMatrices camMatrices;

struct WorldMatrix
{
	DirectX::XMMATRIX worldMatrix;
};
//WorldMatrix worldMatrix;

struct LightStruct
{
	DirectX::XMFLOAT4 lightPosition;
	DirectX::XMFLOAT4 lightColor;
	float intensity;
	DirectX::XMFLOAT3 pad;
};