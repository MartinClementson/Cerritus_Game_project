#include "Camera.h"
#include "Source\Constants.h"


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
	float fovangleY = DirectX::XM_PI * 0.45;
	float aspectRatio = WIN_WIDTH / WIN_HEIGHT;
	float nearZ = 0.01;
	float farZ = 50.0;

	//camMatrices.camView = DirectX::XMMatrixLookAtLH(
		//()
	//);
}

void Camera::TranslateTo(DirectX::XMFLOAT3 newPos)
{

}
