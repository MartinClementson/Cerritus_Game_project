#pragma once

#include "../LibIncluder.h"

struct PointLight
{
	PointLight() { ZeroMemory(this, sizeof(this)); };

	DirectX::XMFLOAT4 lightPosition;
	DirectX::XMFLOAT4X4 lightView;
	DirectX::XMFLOAT4X4 lightProjection;
	DirectX::XMFLOAT4 lightLookAt;
	DirectX::XMFLOAT4 lightDiffuse;
	float intensity;
	DirectX::XMFLOAT3 Pad;
	void SetMatrices(float fov, float aspectRatio, float nearZ, float farZ) {

		DirectX::XMMATRIX tempView = DirectX::XMMatrixLookAtLH(
			DirectX::XMLoadFloat4(&this->lightPosition),
			DirectX::XMLoadFloat4(&this->lightLookAt),
			DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));

		DirectX::XMStoreFloat4x4(&this->lightView, DirectX::XMMatrixTranspose(tempView));

		//DirectX::XMMATRIX tempProj = DirectX::XMMatrixOrthographicLH(2048.0f, 2048.0f, nearZ, farZ);
		DirectX::XMMATRIX tempProj = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
		DirectX::XMStoreFloat4x4(&this->lightProjection, DirectX::XMMatrixTranspose(tempProj));
	};

	PointLight(DirectX::XMFLOAT4 pos, DirectX::XMFLOAT4 dir, DirectX::XMFLOAT4 diffuse)
	{
		this->lightPosition = pos;
		this->lightLookAt = dir;
		this->lightDiffuse = diffuse;
	};



};

struct SpotLight
{
	SpotLight() { ZeroMemory(this, sizeof(this)); };

	DirectX::XMFLOAT4 lightPosition;
	DirectX::XMFLOAT4X4 lightView;
	DirectX::XMFLOAT4X4 lightProjection;
	DirectX::XMFLOAT4 lightLookAt;
	DirectX::XMFLOAT4 lightDiffuse;
	DirectX::XMFLOAT4 lightDiffuse;
	float intensity;
	bool castShadow;

};