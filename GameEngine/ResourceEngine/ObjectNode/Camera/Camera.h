#pragma once
#ifndef  CAMERA_H
#define CAMERA_H
#include "../../ObjectNode/ObjectNode.h"
#include "..\..\..\Source\LibIncluder.h"
#include "..\..\..\Structs\ConstantBufferStruct.h"
#include "../Camera/Frustum/Frustum.h"
#include "../../GameLogic/InputHandler/Input/Input.h"

#define ZOOM 25.0f
using namespace DirectX;

class Camera : ObjectNode
{
private:
	Input* input;
	XMFLOAT3 cameraOffset = { 0.0f, ZOOM ,-ZOOM / 1.75f }; //This is the offset from the players position!
	XMFLOAT4X4 projection;
	XMFLOAT4X4 view;

	LPDIRECTINPUT8 directInput;

	LPDIRECTINPUTDEVICE8 DIMouse;

	DIMOUSESTATE mouseState;
	DIMOUSESTATE mouseLastState;
	
	XMFLOAT3 viewUpDirection;
	XMFLOAT3 viewRightDirection;
	XMFLOAT3 viewPosition;
	XMFLOAT3 viewLookAt;

	CbufferPerFrame camMatrices;
	XMMATRIX camRotationMatrix;

	XMVECTOR defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR defaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR camUpDown = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	float moveLeftRight = 0.0f;		// Used to move along the camFoward and camRight vectors
	float moveBackForward = 0.0f;   // Used to move along the camFoward and camRight vectors
	float moveupDown = 0.0f;

	XMVECTOR camPositionVector = XMVectorSet(0, 2, 0, 0);
	XMVECTOR camTargetVector = XMVectorSet(0, 0, 0, 0);

	XMFLOAT4 camPosition	= { 0, 1, 1, 1  };
	XMFLOAT4 camTarget		= { 1, 0, -1,  1  };
	XMFLOAT4 camUp			= { 0, 1, 0,  0  };

	float camYaw = 0.0f;
	float camPitch = 0.0f;


	bool freeCam			= false;
	float timer				= 0.0f;


public:
	Camera();
	~Camera();

	Frustum * frustum;

	void Update(double deltaTime);
	void ProcessInput(double deltaTime);
	void Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext);
	void FreeCamera(double deltaTime);
	void Release();

	void UpdateView( DirectX::XMFLOAT3 playerPos);
	
	
	CbufferPerFrame* GetCameraMatrices();



};
#endif // ! CAMERA_H


