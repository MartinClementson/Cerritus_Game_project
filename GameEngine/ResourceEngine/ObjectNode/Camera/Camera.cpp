#include "Camera.h"
#include "..\..\..\Source\Constants.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Render()
{
	//???
}

void Camera::Update()
{
	// Vad behövs göras här ???
}

void Camera::Initialize(ID3D11Device *gDevice,ID3D11DeviceContext *gDeviceContext)
{
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
}

void Camera::Updateview(ID3D11Buffer * constBuffer, ID3D11DeviceContext *gDeviceContext)
{
	float fovangleY = XM_PI * 0.45f;
	float aspectRatio = WIN_WIDTH / WIN_HEIGHT;
	float nearZ = 0.01f;
	float farZ = 50.0f;

	camMatrices.camView = XMMatrixLookAtLH(
		(camPosition),
		(camTarget),
		(camUp)
	);

	camMatrices.projection = XMMatrixPerspectiveLH(
		(fovangleY),
		(aspectRatio),
		(nearZ),
		(farZ)
	);

	camMatrices.camView = XMMatrixTranspose(camMatrices.camView);
	camMatrices.projection = XMMatrixTranspose(camMatrices.projection);
	worldMatrix.worldMatrix = XMMatrixIdentity();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gDeviceContext->Map(constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	CamMatrices* tempCamMatrices = (CamMatrices*)mappedResource.pData;
	tempCamMatrices = &camMatrices;

	gDeviceContext->Unmap(constBuffer, 0);
	gDeviceContext->GSGetConstantBuffers(1, 1, &constBuffer);
}

void Camera::TranslateTo(XMFLOAT3 newPos) // Förklaring :
{
	// ???
}

void Camera::Release()
{

}