#pragma once

#include "../LibIncluder.h"

struct PointLight
{


	DirectX::XMFLOAT4		lightPosition;
	DirectX::XMFLOAT4X4		lightView;
	DirectX::XMFLOAT4X4		lightProjection;
	DirectX::XMFLOAT4		lightLookAt;
	DirectX::XMFLOAT4		lightDiffuse;
	float intensity;
	float padIntensity[3];

	float lightRange;
	float padRange[3];

	float attenuation;
	float padatt[3];
	
	BOOL castShadow;
	float padShadow[3];

	
	PointLight() { 
		
		ZeroMemory(this, sizeof(this)); 
		lightPosition	 = DirectX::XMFLOAT4(0.0f,  1.0f,  0.0f,1.0f);
		lightLookAt		 = DirectX::XMFLOAT4(0.0f, -2.0f, 0.0f, 1.0f);
		lightDiffuse	 = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	
		 intensity		 = 1.0f;
		 lightRange		 = 10.0f;
		 attenuation	 = 80;
		 castShadow		 = FALSE;
	
	
	};
	

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

	
	SpotLight() {

		ZeroMemory(this, sizeof(this));
		lightPosition	 = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		lightLookAt		 = DirectX::XMFLOAT4(0.0f, -2.0f, 0.0f, 1.0f);
		lightDiffuse	 = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		intensity		 = 1.0f;
		lightRange		 = 10.0f;
		spotRadius		 = 80.0f;
		attenuation		 = 0.05f;
		castShadow		 = FALSE;


	};

	DirectX::XMFLOAT4	 lightPosition;
	DirectX::XMFLOAT4X4  lightView;
	DirectX::XMFLOAT4X4  lightProjection;
	DirectX::XMFLOAT4	 lightLookAt;
	DirectX::XMFLOAT4	 lightDiffuse;
						 
	float intensity;
	float lightRange;
	float attenuation;
	float spotRadius;

	BOOL castShadow;
	

};



struct DirectionalLight
{

	DirectionalLight() {

		ZeroMemory(this, sizeof(this));
		lightPosition = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		lightLookAt = DirectX::XMFLOAT4(0.0f, -2.0f, 0.0f, 1.0f);
		lightDiffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		intensity = 1.0f;
		castShadow = FALSE;
	};

	DirectX::XMFLOAT4	 lightPosition;
	DirectX::XMFLOAT4X4  lightView;
	DirectX::XMFLOAT4X4  lightProjection;
	DirectX::XMFLOAT4	 lightLookAt;
	DirectX::XMFLOAT4	 lightDiffuse;

	float intensity;
	DirectX::XMFLOAT3 pad;
	
	BOOL castShadow;




	void SetMatrices(float fov, float aspectRatio, float nearZ, float farZ) {

		DirectX::XMMATRIX tempView = DirectX::XMMatrixLookAtLH(
			DirectX::XMLoadFloat4(&this->lightPosition),
			DirectX::XMLoadFloat4(&this->lightLookAt),
			DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));

		DirectX::XMStoreFloat4x4(&this->lightView, DirectX::XMMatrixTranspose(tempView));

		DirectX::XMMATRIX tempProj = DirectX::XMMatrixOrthographicLH(2048.0f, 2048.0f, nearZ, farZ);
		
		DirectX::XMStoreFloat4x4(&this->lightProjection, DirectX::XMMatrixTranspose(tempProj));
	};

	DirectionalLight(DirectX::XMFLOAT4 pos, DirectX::XMFLOAT4 dir, DirectX::XMFLOAT4 diffuse,float intensity)
	{
		this->intensity			= intensity;
		this->lightPosition		= pos;
		this->lightLookAt	    = dir;
		this->lightDiffuse		= diffuse;
	};



};