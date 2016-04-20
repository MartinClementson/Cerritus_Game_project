#pragma once
#ifndef  CAMERA_H
#define CAMERA_H
#include "../../ObjectNode/ObjectNode.h"
#include "..\..\..\Source\LibIncluder.h"
#include "..\..\..\Structs\ConstantBufferStruct.h"

#define ZOOM 10.0f
using namespace DirectX;

class Camera : ObjectNode
{
private:

	XMFLOAT3 cameraOffset = { 0.0f, ZOOM ,-ZOOM }; //This is the offset from the players position!
	XMFLOAT4X4 projection;
	XMFLOAT4X4 view;

	XMFLOAT3 viewUpDirection;
	XMFLOAT3 viewRightDirection;
	XMFLOAT3 viewPosition;
	XMFLOAT3 viewLookAt;

	CamMatrices camMatrices;


	XMFLOAT4 camPosition	= { 0, 1, 1, 1  };
	XMFLOAT4 camTarget		= { 1, 0, -1,  1  };
	XMFLOAT4 camUp			= { 0, 1, 0,  0  };

public:
	Camera();
	~Camera();


	void Update();
	void Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext);
	void Release();

	void Updateview( DirectX::XMFLOAT3 playerPos);
	
	
	CamMatrices* GetCameraMatrices();



};
#endif // ! CAMERA_H


