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

void Camera::Updateview(ID3D11Buffer * constBuffer)
{
	float fovangleY = DirectX::XM_PI * 0.45f;
	float aspectRatio = float(WIN_WIDTH / WIN_HEIGHT);
	float nearZ = 0.01f;
	float farZ = 50.0f;

	//camMatrices.camView = DirectX::XMMatrixLookAtLH(
		//()
	//);
}

void Camera::TranslateTo(DirectX::XMFLOAT3 newPos)
{

}
