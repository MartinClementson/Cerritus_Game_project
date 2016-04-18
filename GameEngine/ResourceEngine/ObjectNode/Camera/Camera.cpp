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
	this->gDevice				 = gDevice;
	this->gDeviceContext		 = gDeviceContext;



	//_____________________________________________________________________________________________
	//									Projection Matrix
	float fovangleY				 = XM_PI * 0.45f;
	float aspectRatio			 = float(WIN_WIDTH / WIN_HEIGHT);
	float farZ					 = 50.0f;
	float nearZ					 = 0.01f;


	//Create projection Matrix
	DirectX::XMMATRIX tempProj	 = XMMatrixPerspectiveLH(
		(fovangleY),
		(aspectRatio),
		(nearZ),
		(farZ)
		);
	//Transpose the Projcetion matrix
	tempProj = XMMatrixTranspose(tempProj);

	//Store The projection
	XMStoreFloat4x4(&camMatrices.projection,tempProj);


	//_________________________________________________________________________________________
	//                                     VIEW MATRIX
	
	//Create the view matrix
		DirectX::XMMATRIX tempView = XMMatrixLookAtLH(
		(XMLoadFloat4(&camPosition)),
		(XMLoadFloat4(&camTarget)),
		(XMLoadFloat4(&camUp))
		);


	//Transpose view matrix
	tempView = XMMatrixTranspose(tempView);

	//store the view matrix
	XMStoreFloat4x4(&camMatrices.camView, tempProj);
	
	
}

void Camera::Updateview(ID3D11Buffer * constBuffer, DirectX::XMFLOAT2 playerPos)
{
	//Update the position of the camera to follow the player

	camPosition.x = playerPos.x + cameraOffset.x;
	camPosition.y = cameraOffset.y;
	camPosition.z = playerPos.y + cameraOffset.z; //The y here is NOT a mistake.

	//update the struct with the new position
	this->camMatrices.worldPos = this->camPosition;
	
	XMMATRIX tempView = XMMatrixLookAtLH(
		(XMLoadFloat4(&camPosition)),
		(XMLoadFloat4(&camTarget)),
		(XMLoadFloat4(&camUp)) );

	tempView = XMMatrixTranspose(tempView);


	XMStoreFloat4x4(&camMatrices.camView, XMMatrixTranspose(tempView));



	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gDeviceContext->Map(constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	CamMatrices* tempCamMatrices = (CamMatrices*)mappedResource.pData;
	tempCamMatrices = &camMatrices;

	gDeviceContext->Unmap(constBuffer, 0);
	gDeviceContext->GSGetConstantBuffers(1, 1, &constBuffer);
}

void Camera::TranslateTo(XMFLOAT3 newPos) // Förklaring : Translate to -> new pos
{
	// ???
}

void Camera::Release()
{

}