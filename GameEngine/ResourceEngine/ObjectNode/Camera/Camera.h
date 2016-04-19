#pragma once
#ifndef  CAMERA_H
#define CAMERA_H
#include "../../ObjectNode/ObjectNode.h"
#include "..\..\..\Source\LibIncluder.h"
#include "..\..\..\Structs\ConstantBufferStruct.h"


using namespace DirectX;

class Camera : ObjectNode
{
private:
	XMFLOAT4X4 projection;
	XMFLOAT4X4 view;

	XMFLOAT3 viewUpDirection;
	XMFLOAT3 viewRightDirection;
	XMFLOAT3 viewPosition;
	XMFLOAT3 viewLookAt;

	CamMatrices camMatrices;
	WorldMatrix worldMatrix;

	XMVECTOR camPosition = XMVectorSet(0, 1, -1, 0);
	XMVECTOR camTarget = XMVectorSet(0, 0, 0, 0);
	XMVECTOR camUp = XMVectorSet(0, 1, 0, 0);
private:

public:
	Camera();
	~Camera();

	void Render();
	void Update();
	void Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext);
	void Release();

	void Updateview(ID3D11Buffer *constBuffer , ID3D11DeviceContext *gDevice);
	void TranslateTo(XMFLOAT3 newPos);




};
#endif // ! CAMERA_H


