#pragma once
#ifndef  CAMERA_H
#define CAMERA_H
#include "..\..\..\Source\LibIncluder.h"
#include "..\..\..\Structs\ConstantBufferStruct.h"

using namespace DirectX;

class Camera
{
private:
	XMFLOAT4X4 projection;
	XMFLOAT4X4 view;

	XMFLOAT3 viewUpDirection;
	XMFLOAT3 viewRightDirection;
	XMFLOAT3 viewPosition;
	XMFLOAT3 viewLookAt;

private:

public:
	Camera();
	~Camera();

	void Render();
	void Update();
	void Initialize();
	void Release();

	void Updateview(ID3D11Buffer *constBuffer , ID3D11DeviceContext *gDevice);
	void TranslateTo(XMFLOAT3 newPos);




};
#endif // ! CAMERA_H


