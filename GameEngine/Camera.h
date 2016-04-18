#pragma once
#ifndef  CAMERA_H
#define CAMERA_H
#include "Source\LibIncluder.h"
#include "Structs\ConstantBufferStruct.h"

class Camera
{
private:
	DirectX::XMFLOAT4X4 projection;
	DirectX::XMFLOAT4X4 view;

	DirectX::XMFLOAT3 viewUpDirection;
	DirectX::XMFLOAT3 viewRightDirection;
	DirectX::XMFLOAT3 viewPosition;
	DirectX::XMFLOAT3 viewLookAt;

private:

public:
	Camera();
	~Camera();

	void Render();
	void Update();
	void Initialize();
	void Release();

	void Updateview(ID3D11Buffer *constBuffer);
	void TranslateTo(DirectX::XMFLOAT3 newPos);




};
#endif // ! CAMERA_H


