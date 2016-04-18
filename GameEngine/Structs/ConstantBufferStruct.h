#pragma once

#include "../Source/LibIncluder.h"

struct CamMatrices
{
	DirectX::XMMATRIX camView;
	DirectX::XMMATRIX projection;
};
CamMatrices camMatrices;

struct WorldMatrix
{
	DirectX::XMMATRIX worldMatrix;
};
WorldMatrix wordlMatrix;