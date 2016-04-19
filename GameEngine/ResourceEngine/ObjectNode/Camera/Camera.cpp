#include "Camera.h"
#include "..\..\..\Source\Constants.h"


Camera::Camera()
{
}


Camera::~Camera()
{
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
	float farZ					 = 50000.0f;
	float nearZ					 = 0.01f;


	//Create projection Matrix
	DirectX::XMMATRIX tempProj	 = XMMatrixPerspectiveFovLH(
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

void Camera::Updateview( DirectX::XMFLOAT3 playerPos)
{
	//Update the position of the camera to follow the player
	
	static float translate = 0;
	translate += 0.01f;



	camPosition.x = playerPos.x + cameraOffset.x;
	camPosition.y = cameraOffset.y;
	camPosition.z = playerPos.z + cameraOffset.z;

	//update the struct with the new position
	this->camMatrices.worldPos = this->camPosition;

	//update the look at
	camTarget.x = playerPos.x;
	camTarget.y = playerPos.y;
	camTarget.z = playerPos.z;

	
	XMMATRIX tempView = XMMatrixLookAtLH(
		(XMLoadFloat4(&camPosition)),
		(XMLoadFloat4(&camTarget)),
		(XMLoadFloat4(&camUp)) );

	


	XMStoreFloat4x4(&camMatrices.camView, XMMatrixTranspose(tempView));

}

void Camera::TranslateTo(XMFLOAT3 newPos) // Förklaring : Translate to -> new pos
{
	// ???
}

CamMatrices * Camera::GetCameraMatrices()
{

	return &this->camMatrices;
}

void Camera::Release()
{

}