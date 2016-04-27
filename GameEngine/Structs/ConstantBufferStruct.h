#pragma once

#include "../Source/LibIncluder.h"

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
	DirectX::XMFLOAT4 lightPosition;
	DirectX::XMFLOAT4X4 lightView;
	DirectX::XMFLOAT4X4 lightProjection;
	DirectX::XMFLOAT4 lightDir;
	DirectX::XMFLOAT4 lightDiffuse;
	float intensity;
	DirectX::XMFLOAT3 Pad;
	void SetMatrices(float fov, float aspectRatio, float nearZ, float farZ) {
		
		DirectX::XMMATRIX tempView = DirectX::XMMatrixLookAtLH(
			DirectX::XMLoadFloat4(&this->lightPosition),
			DirectX::XMLoadFloat4(&this->lightDir),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

		DirectX::XMStoreFloat4x4(&this->lightView, DirectX::XMMatrixTranspose(tempView));

		//DirectX::XMMATRIX tempProj = DirectX::XMMatrixOrthographicLH(2048.0f, 2048.0f, nearZ, farZ);
		DirectX::XMMATRIX tempProj = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
		DirectX::XMStoreFloat4x4(&this->lightProjection, DirectX::XMMatrixTranspose(tempProj));
	};

	LightStruct() {};
	LightStruct(DirectX::XMFLOAT4 pos, DirectX::XMFLOAT4 dir, DirectX::XMFLOAT4 diffuse)
	{
		this->lightPosition			 = pos;
		this->lightDir				 = dir;
		this->lightDiffuse			 = diffuse;
	};


};


struct SampleBoolStruct
{

	BOOL diffuseMap	 = FALSE	;
	BOOL normalMap	 = FALSE	;
	BOOL specularMap = FALSE	;
	BOOL glowMap	 = FALSE	;
};
