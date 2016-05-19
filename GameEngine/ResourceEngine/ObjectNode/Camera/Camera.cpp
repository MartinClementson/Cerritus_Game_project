#include "Camera.h"
#include "..\..\..\Source\Constants.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::Update(double deltaTime)
{
	this->ProcessInput(deltaTime);
}

void Camera::ProcessInput(double deltaTime)
{

	
	timer += (float)deltaTime;

	if (input->IsKeyPressed(KEY_C) && timer > 0.2f)
	{
		if (this->freeCam == false)
		{
			DIMouse = input->GetMouse();
			//ShowCursor(TRUE);
			this->freeCam = true;
		}
		else if (this->freeCam == true)
		{
			DIMouse = input->GetMouse();
			//ShowCursor(FALSE);
			this->freeCam = false;
		}
		timer = 0.0f;
	}
	if (freeCam)
	{
		float speed = 25.0f * (float)deltaTime;

		DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
		if (input->IsKeyPressed(KEY_LEFT))
		{
			moveLeftRight -= speed;
		}
		if (input->IsKeyPressed(KEY_RIGHT))
		{
			moveLeftRight += speed;
		}
		if (input->IsKeyPressed(KEY_UP))
		{
			moveBackForward += speed;
		}
		if (input->IsKeyPressed(KEY_DOWN))
		{
			moveBackForward -= speed;
		}
		if (input->IsKeyPressed(KEY_PGDWN))
		{
			moveupDown -= speed;
		}
		if (input->IsKeyPressed(KEY_PGUP))
		{
			moveupDown += speed;
		}
		if ((mouseState.lX != mouseLastState.lX) || (mouseState.lY != mouseLastState.lY))
		{
			camYaw += mouseState.lX * (float)deltaTime;

			camPitch += mouseState.lY * (float)deltaTime;

			mouseLastState = mouseState;
		}

		FreeCamera(deltaTime);
	}

}

void Camera::Initialize(ID3D11Device *gDevice,ID3D11DeviceContext *gDeviceContext)
{
	
	this->gDevice				 = gDevice;
	this->gDeviceContext		 = gDeviceContext;
	this->input = Input::GetInstance();

	//_____________________________________________________________________________________________
	//									Projection Matrix
	float fovangleY				 = XM_PI * 0.45f;
	float aspectRatio			 = float(WIN_WIDTH / WIN_HEIGHT);
	float farZ					 = 200.0f;
	float nearZ					 = 0.01f;


	//Create projection Matrix
	DirectX::XMMATRIX tempProj	 = XMMatrixPerspectiveFovLH(
		(fovangleY),
		(aspectRatio),
		(nearZ),
		(farZ)
		);

	XMMATRIX frustumProj = tempProj;
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

	XMMATRIX frustumView = tempView;
	//Transpose view matrix
	tempView = XMMatrixTranspose(tempView);

	//store the view matrix
	XMStoreFloat4x4(&camMatrices.camView, tempProj);

	this->frustum = new Frustum;
	XMFLOAT4X4 frustumProjFloat;
	XMStoreFloat4x4(&frustumProjFloat,frustumProj);
	XMFLOAT4X4 frustumViewFloat;
	XMStoreFloat4x4(&frustumViewFloat, frustumView);
	frustum->CreateFrustum(farZ, frustumProjFloat, frustumViewFloat);


	
}

void Camera::FreeCamera(double deltaTime)
{
	
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0); // Used to rotate around all the axis at the same time with the functoin XMMatixRotationpitchyaw
	camTargetVector = XMVector3TransformCoord(defaultForward, camRotationMatrix); // sets the camera target vector by rotating the defaultforward vector with the
																			// rotation matrix we created
	camTargetVector = XMVector3Normalize(camTargetVector); // normalizing the camtarget vector

	
	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw); // Finding the new right and forward directions of the camera by  using a rotation matrix 
												   //which will be rotated on the Y-axis, since its a first perosn camera we need to keep our cam forward and right pointing only in x and z axis
												   // transforming the cameras right up and forwards vectors using the matrix just defined.
												   // also rotating the default right up and default foward vectors and set the result in the right up and foward vectors.
	/**/ camRight = XMVector3TransformCoord(defaultRight, RotateYTempMatrix);
	/**/ camUpDown = XMVector3TransformCoord(defaultUp, RotateYTempMatrix);
	/**/ camForward = XMVector3TransformCoord(defaultForward, RotateYTempMatrix);

	camPositionVector += moveLeftRight* camRight;
	camPositionVector += moveBackForward* camForward;
	camPositionVector += moveupDown * camUpDown;

	XMStoreFloat4(&camPosition, camPositionVector);

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;
	moveupDown = 0.0f;

	//Update the position of the camera to follow the player

	camTargetVector = camPositionVector + camTargetVector;

	XMStoreFloat4(&camTarget, camTargetVector);


	
	//update the struct with the new position
	this->camMatrices.worldPos = this->camPosition;

	//update the look at


	//DENNA SKA FLYTTAS
	XMMATRIX tempView = XMMatrixLookAtLH( //Create view matrix
		(XMLoadFloat4(&camPosition)),
		(XMLoadFloat4(&camTarget)),
		(XMLoadFloat4(&camUp)));


	XMStoreFloat4x4(&camMatrices.camView, XMMatrixTranspose(tempView));

	//We also have to update the invViewProjMatrix!
	XMMATRIX proj = XMLoadFloat4x4(&camMatrices.projection);
	proj = XMMatrixTranspose(proj); // transpose it back to cpu alignment
	XMMATRIX frustumProj = proj;

	XMMATRIX viewProjInv = XMMatrixMultiply(tempView, proj);

	XMVECTOR det = XMMatrixDeterminant(viewProjInv);

	viewProjInv = XMMatrixInverse(&det, viewProjInv);

	XMStoreFloat4x4(&camMatrices.invViewProjMatrix, XMMatrixTranspose(viewProjInv));

	XMMATRIX view = XMLoadFloat4x4(&camMatrices.camView);
	view = XMMatrixTranspose(view); // transpose it back to cpu alignment
	XMMATRIX frustumView = view;

	XMFLOAT4X4 frustumProjFloat;
	XMStoreFloat4x4(&frustumProjFloat, frustumProj);
	XMFLOAT4X4 frustumViewFloat;
	XMStoreFloat4x4(&frustumViewFloat, frustumView);

	frustum->CreateFrustum(200.0f, frustumProjFloat, frustumViewFloat);

}

void Camera::UpdateView( DirectX::XMFLOAT3 playerPos)
{


	if (!this->freeCam)
	{
		//Update the position of the camera to follow the player

		camPosition.x = playerPos.x + cameraOffset.x;
		camPosition.y = cameraOffset.y;
		camPosition.z = playerPos.z + cameraOffset.z;

		//update the struct with the new position
		this->camMatrices.worldPos = this->camPosition;

		//update the look at
		camTarget.x = playerPos.x;
		camTarget.y = 0.0f;
		camTarget.z = playerPos.z;



		XMMATRIX tempView = XMMatrixLookAtLH( //Create view matrix
			(XMLoadFloat4(&camPosition)),
			(XMLoadFloat4(&camTarget)),
			(XMLoadFloat4(&camUp)));




		XMStoreFloat4x4(&camMatrices.camView, XMMatrixTranspose(tempView));

		//We also have to update the invViewProjMatrix!
		XMMATRIX proj = XMLoadFloat4x4(&camMatrices.projection);
		proj = XMMatrixTranspose(proj); // transpose it back to cpu alignment
		XMMATRIX frustumProj = proj;

		XMMATRIX viewProjInv = XMMatrixMultiply(tempView, proj);

		XMVECTOR det = XMMatrixDeterminant(viewProjInv);

		viewProjInv = XMMatrixInverse(&det, viewProjInv);

		XMStoreFloat4x4(&camMatrices.invViewProjMatrix, XMMatrixTranspose(viewProjInv));

		XMMATRIX view = XMLoadFloat4x4(&camMatrices.camView);
		view = XMMatrixTranspose(view); // transpose it back to cpu alignment
		XMMATRIX frustumView = view;

		XMFLOAT4X4 frustumProjFloat;
		XMStoreFloat4x4(&frustumProjFloat, frustumProj);
		XMFLOAT4X4 frustumViewFloat;
		XMStoreFloat4x4(&frustumViewFloat, frustumView);

		frustum->CreateFrustum(200.0f, frustumProjFloat, frustumViewFloat);
	}
}

CbufferPerFrame * Camera::GetCameraMatrices()
{

	return &this->camMatrices;
}

void Camera::Release()
{
	delete this->frustum;
}