#pragma once

#include "../Source/LibIncluder.h"

struct CamMatrices
{
	DirectX::XMMATRIX camView;
	DirectX::XMMATRIX projection;
	DirectX::XMFLOAT3 worldPos;
};
//CamMatrices camMatrices;

struct WorldMatrix
{
	DirectX::XMMATRIX worldMatrix;
};
//WorldMatrix worldMatrix;

struct LightStruct
{
	//Stubby stub stub
};