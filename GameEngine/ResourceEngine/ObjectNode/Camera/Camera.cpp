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

}

void Camera::Update()
{

}

void Camera::Initialize()
{

}

void Camera::Release()
{

}

void Camera::Updateview(ID3D11Buffer * constBuffer, ID3D11DeviceContext *gDeviceContext)
{
	XMVECTOR camPosition = XMVectorSet(0, 1, -5, 0);
	XMVECTOR camTarget = XMVectorSet(0, 0, 0, 0);
	XMVECTOR camUp = XMVectorSet(0, 1, 0, 0);

	float fovangleY = DirectX::XM_PI * 0.45;
	float aspectRatio = WIN_WIDTH / WIN_HEIGHT;
	float nearZ = 0.01;
	float farZ = 50.0;

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

	gDeviceContext->UpdateSubresource(constBuffer, 0, 0, &camMatrices, 0, 0);

	/*D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));*/

	//gDeviceContext->Map(constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//memcpy(mappedResource.pData, &constBuffer,sizeof());
	//gDeviceContext->Unmap(constBuffer, 0);

	
}

void Camera::TranslateTo(DirectX::XMFLOAT3 newPos)
{

}
