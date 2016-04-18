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

	XMFLOAT3 cameraOffset = { 0.0f,5.0f,0.0f }; //This is the offset from the players position!
	XMFLOAT4X4 projection;
	XMFLOAT4X4 view;

	XMFLOAT3 viewUpDirection;
	XMFLOAT3 viewRightDirection;
	XMFLOAT3 viewPosition;
	XMFLOAT3 viewLookAt;

	CamMatrices camMatrices;
	WorldMatrix worldMatrix;

	XMFLOAT4 camPosition	= { 0, 1, -1, 0  };
	XMFLOAT4 camTarget		= { 0, 0, 0,  0  };
	XMFLOAT4 camUp			= { 0, 1, 0,  0  };

public:
	Camera();
	~Camera();

	void Render();
	void Update();
	void Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext);
	void Release();

	void Updateview(ID3D11Buffer *constBuffer, DirectX::XMFLOAT2 playerPos);
	void TranslateTo(XMFLOAT3 newPos);




};
#endif // ! CAMERA_H


