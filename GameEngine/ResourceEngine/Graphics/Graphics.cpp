#include "Graphics.h"
#define toRadian(degrees) ((degrees)* (XM_PI/180.0f))

inline DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}

inline DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 a, float b) {
	DirectX::XMFLOAT3 result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;

	return result;
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	if (gameObjects != nullptr)
		delete gameObjects;
	if (charObjects != nullptr)
		delete charObjects;
	if (uiObjects != nullptr)
		delete uiObjects;
	if (enemyObjects != nullptr)
		delete enemyObjects;
	if (trapObjects != nullptr)
		delete trapObjects;

	if (shadowBuffer != nullptr)
		delete shadowBuffer;
	if (renderer != nullptr)
		delete renderer;

	if (gBuffer != nullptr)
		delete gBuffer;

	if (instancedWorldDataPerFrame != nullptr)
	{
		for (size_t i = 0; i < INSTANCED_WORLD_BUFFER_AMOUNT; i++)
		{

			delete instancedWorldDataPerFrame[i];
		}
	}

	
}

void Graphics::Initialize(HWND * window)
{
	HRESULT hr;
	this->wndHandle  = window;

	hr				 = CreateDirect3DContext();

	gameObjects		 = new std::vector<RenderInfoObject*>;
	charObjects		 = new std::vector<RenderInfoChar*>;
	uiObjects		 = new std::vector<RenderInfoUI*>;
	enemyObjects	 = new std::vector<RenderInfoEnemy*>;
	trapObjects		 = new std::vector<RenderInfoTrap*>;

	instancedWorldDataPerFrame[ENEMY_1_INSTANCED]    = new InstancedData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[PROJECTILE_INSTANCED] = new InstancedData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED]	 = new InstancedData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED]	 = new InstancedData[MAX_INSTANCED_GEOMETRY];

	
	memset(billBoardArray,	  0, sizeof(billBoardArray));
	memset(instancesToRender, 0, sizeof(instancesToRender)); //reset instances to render amount

	renderer = new Renderer();
	renderer->Initialize(gDevice,this->gDeviceContext);
	
	gBuffer = new Gbuffer();
	gBuffer->Initialize(this->gDevice,this->gDeviceContext);

	shadowBuffer = new ShadowBuffer();
	shadowBuffer->Initialize(this->gDevice, this->gDeviceContext);
}

void Graphics::Release()
{

#pragma region Release custom classes

	renderer->Release();
#pragma endregion




	gBuffer->Release();
	shadowBuffer->Release();

	SAFE_RELEASE(depthState);
	SAFE_RELEASE(depthStencilView);
	SAFE_RELEASE(depthBuffer);


	SAFE_RELEASE(gBackBufferUAV);
	SAFE_RELEASE(BackBufferTexture);


	SAFE_RELEASE(gBackBufferRTV);
	gSwapChain->SetFullscreenState(false, nullptr);
	SAFE_RELEASE(gSwapChain);
	gDeviceContext->ClearState();
	SAFE_RELEASE(gDeviceContext);



	if (DEBUG == 2)
	{
		if (debug)
		{
			debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
			SAFE_RELEASE(debug);
		}
	}
	while (gDevice->Release() > 0);
	//SAFE_RELEASE(gDevice);

	
}

void Graphics::Render() //manage RenderPasses here
{
	renderer->UpdateCamera(charObjects->at(0)->position);
	CullGeometry(); //Remove geometry out of reach

	SetShadowViewPort();

	shadowBuffer->ClearShadowGbuffer();

	shadowBuffer->ShadowSetToRender();
	renderer->SetShadowPass(true);

	this->RenderScene();

	gBuffer->SetToRender(depthStencilView);	
	shadowBuffer->ShadowSetToRead();
	renderer->SetShadowPass(false);
	SetViewPort();




	//this->gDeviceContext->OMSetRenderTargets(1, &this->gBackBufferRTV, depthStencilView);

			//Set The gbuffer pass
	this->renderer->SetGbufferPass(true);
	RenderScene();									//Render to the gBuffer
													//Set the gBuffer as a subResource, send in the new RenderTarget
	gBuffer->SetToRead(gBackBufferRTV); 
	
	//blurpass
	this->renderer->RenderBlurPass(this->gBuffer->GetBlurUAV(), this->gBuffer->GetGlowSRV());

	this->renderer->RenderFinalPass();
	gBuffer->ClearGbuffer();
	this->renderer->SetGbufferPass(false);
	
	//RenderScene();// TEMPORARY, REMOVE WHEN GBUFFER WORKS

	FinishFrame();


}

void Graphics::RenderScene()
{

	//Always render the char first! This is because we set the camera matrix with the characters position
	if (charObjects->size() != 0)
	{
		renderer->Render(charObjects->at(0));
	}
#pragma region Temporary code for early testing
	RenderInfoObject tempInfo;						//TEMPORARY
													//TEMPORARY
	tempInfo.position = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.object = MeshEnum::LEVEL_1;
	this->renderer->Render(&tempInfo);				//TEMPORARY
	tempInfo.position = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.object = MeshEnum::LEVEL_2;
	this->renderer->Render(&tempInfo);				//TEMPORARY
	tempInfo.position = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.object = MeshEnum::LEVEL_3;
	this->renderer->Render(&tempInfo);				//TEMPORARY
	tempInfo.position = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f); //TEMPORARY
	tempInfo.object = MeshEnum::LEVEL_4;
	this->renderer->Render(&tempInfo);				 //TEMPORARY

#pragma endregion





	for (unsigned int i = 0; i < gameObjects->size(); i++)
	{
		if (!gameObjects->at(i)->render)
			continue;
		else
			renderer->Render(gameObjects->at(i));

	}

	//Render instanced projectiles
	if (instancesToRender[PROJECTILE_INSTANCED] > 0)
	{
		////////////BILLBOARD RENDERING
 		renderer->RenderBillBoard(this->gameObjects->at(instanceMeshIndex.projectileMesh), billBoardArray, instancesToRender[PROJECTILE_INSTANCED]);
		//////////////INSTANCE RENDERING
		//renderer->RenderInstanced(this->gameObjects->at(instanceMeshIndex.projectileMesh),
			//instancedWorldDataPerFrame[ PROJECTILE_INSTANCED ], instancesToRender[ PROJECTILE_INSTANCED ] );
	}



	////Render instanced enemies
	if (instancesToRender[ENEMY_1_INSTANCED] > 0)
	{
		renderer->RenderInstanced(this->enemyObjects->at(instanceMeshIndex.enemy1Mesh ),
			instancedWorldDataPerFrame[ ENEMY_1_INSTANCED ], instancesToRender[ ENEMY_1_INSTANCED ]);
	}
	
	 //Take back when we have more enemy types
	/*for (unsigned int i = 0; i < enemyObjects->size(); i++)
	{
		if (!enemyObjects->at(i)->render)
			continue;
		else
			renderer->Render(enemyObjects->at(i));
	}*/

	////Render instanced FireTraps
	if (instancesToRender[TRAP_FIRE_INSTANCED] > 0)
	{
		renderer->RenderInstanced(this->trapObjects->at(instanceMeshIndex.trapFireMesh),
			instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED], instancesToRender[TRAP_FIRE_INSTANCED]);
	}

	////Render instanced BearTraps
	if (instancesToRender[TRAP_BEAR_INSTANCED] > 0)
	{
		renderer->RenderInstanced(this->trapObjects->at(instanceMeshIndex.trapBearMesh),
			instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED], instancesToRender[TRAP_BEAR_INSTANCED]);
	}




	/*for (unsigned int i = 0; i < trapObjects->size(); i++)
	{
		if (!trapObjects->at(i)->render)
			continue;
		else
			renderer->Render(trapObjects->at(i));

	}*/

	for (unsigned int i = 0; i < uiObjects->size(); i++)
	{
		renderer->Render(uiObjects->at(i));

	}



}

void Graphics::FinishFrame() // this one clears the graphics for this frame. So that it can start a new cycle next frame
{
	gameObjects  ->clear(); //clear the queue
	charObjects  ->clear();	//clear the queue
	enemyObjects ->clear();	//clear the queue
	trapObjects	 ->clear();	//clear the queue
	uiObjects	 ->clear();	//clear the queue

	memset(instancedWorldDataPerFrame[ENEMY_1_INSTANCED],    0, sizeof(instancedWorldDataPerFrame[ENEMY_1_INSTANCED]   ));	 //reset instance array
	memset(instancedWorldDataPerFrame[PROJECTILE_INSTANCED], 0, sizeof(instancedWorldDataPerFrame[PROJECTILE_INSTANCED]));   //reset instance array
	memset(instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED],  0, sizeof(instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED]));	 //reset instance array
	memset(instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED],  0, sizeof(instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED]));	 //reset instance array

	memset(billBoardArray, 0, sizeof(billBoardArray));



	
	memset(instancesToRender, 0, sizeof(instancesToRender)); //reset instances to render amount

	instanceMeshIndex.Reset();

	this->gSwapChain->Present(VSYNC, 0); //Change front and back buffer after rendering
	
	float clearColor[] = { 0, 0, 1, 1 };
	this->gDeviceContext->ClearDepthStencilView(this->depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	this->gDeviceContext->ClearRenderTargetView(gBackBufferRTV, clearColor);
	gDeviceContext->ClearState();
	



}

void Graphics::SetViewPort()
{
	vp.Width	= (float)WIN_WIDTH;
	vp.Height	= (float)WIN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	this->gDeviceContext->RSSetViewports(1, &vp);

}

void Graphics::SetShadowViewPort()
{
	vp.Width	=	(float)SHADOW_WIDTH;
	vp.Height	=   (float)SHADOW_HEIGHT;
	vp.MinDepth =	0.0f;
	vp.MaxDepth =	1.0f;
	vp.TopLeftX =	0;
	vp.TopLeftY =	0;
	this->gDeviceContext->RSSetViewports(1, &vp);

}

void Graphics::SetShadowMap()
{

}

void Graphics::CullGeometry()
{


	//Do frustum culling here, the things that are seen have their world matrices calculated. and added to instanced array
	unsigned int	 projectileIndex	 = 0;
	unsigned int	 enemyIndex			 = 0;
	unsigned int	 bearTrapIndex		 = 0;
	unsigned int	 fireTrapIndex		 = 0;

#pragma region Cull enemy objects
	for (size_t i = 0; i < this->enemyObjects->size(); i++)
	{
		//Frustum culling
		if (renderer->FrustumCheck(enemyObjects->at(i)->position, enemyObjects->at(i)->radius) == false)
		{	
			//If its not visible
			this->enemyObjects->at(i)->render = false;
			continue;
		}
		 
		else {

			//if object is visible and is enemy_1_type
			this->instancedWorldDataPerFrame[ENEMY_1_INSTANCED][enemyIndex].worldMatrix = CalculateWorldMatrix(&this->enemyObjects->at(i)->position, &this->enemyObjects->at(i)->rotation);
			instancesToRender		   [ENEMY_1_INSTANCED] += 1;
			enemyIndex									  += 1;
			this->enemyObjects->at(i)->render = false; //Remove this from normal rendering, since we render instanced
				if (instanceMeshIndex.enemy1Mesh == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.enemy1Mesh = (int)i;

				/*if (enemyObjects->at(i)->showHealthBar)
				{

				}*/
		}
		//endif  object is visible
	}
#pragma endregion

#pragma region Cull game objects
 	for (size_t i = 0; i < this->gameObjects->size(); i++)
	{
		//Frustum culling
	if (renderer->FrustumCheck(gameObjects->at(i)->position, gameObjects->at(i)->radius) == false)
		{	//If its not visible
     			this->gameObjects->at(i)->render = false;
			continue;
		}
		else //if it's inside the frustum
		{
 			if (this->gameObjects->at(i)->object == MeshEnum::PROJECTILE_1)
			{

				//this->instancedWorldDataPerFrame[PROJECTILE_INSTANCED][projectileIndex].worldMatrix = CalculateWorldMatrix(&this->gameObjects->at(i)->position, &this->gameObjects->at(i)->rotation);
				billBoardArray[projectileIndex].direction = this->gameObjects->at(i)->direction;
				billBoardArray[projectileIndex].height    = 3.0f;
				billBoardArray[projectileIndex].width     = 0.15f;
				billBoardArray[projectileIndex].worldPos  = this->gameObjects->at(i)->position + (this->gameObjects->at(i)->direction *(billBoardArray[projectileIndex].height * 0.9));

				instancesToRender[PROJECTILE_INSTANCED]  += 1;
				projectileIndex							 += 1;
				this->gameObjects->at(i)->render		  = false; //We don't want to render this with nonInstance rendering
				
				if (instanceMeshIndex.projectileMesh == -1) //if this is the first thing we found of that mesh, store the index.
      					instanceMeshIndex.projectileMesh = (int)i;
			}
			else
				this->gameObjects->at(i)->render = true;

		}

	}

#pragma endregion


#pragma region Cull trap objects

	for (size_t i = 0; i < this->trapObjects->size(); i++)
	{
		//Frustum culling
		if (renderer->FrustumCheck(trapObjects->at(i)->position, trapObjects->at(i)->radius) == false)
		{
			//If its not visible
			this->trapObjects->at(i)->render = false;
			continue;
		}
		else
		{
			if (this->trapObjects->at(i)->object == MeshEnum::TRAP_BEAR)
			{
				this->instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED][bearTrapIndex].worldMatrix = CalculateWorldMatrix(&this->trapObjects->at(i)->position, &this->trapObjects->at(i)->rotation);
				instancesToRender[TRAP_BEAR_INSTANCED] += 1;
				bearTrapIndex += 1;
				this->trapObjects->at(i)->render = false; //We don't want to render this with nonInstance rendering

				if (instanceMeshIndex.trapBearMesh == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.trapBearMesh = (int)i;
			}

			else if (this->trapObjects->at(i)->object == MeshEnum::TRAP_FIRE)
			{
				this->instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED][fireTrapIndex].worldMatrix = CalculateWorldMatrix(&this->trapObjects->at(i)->position, &this->trapObjects->at(i)->rotation);
				instancesToRender[TRAP_FIRE_INSTANCED] += 1;
				fireTrapIndex += 1;
				this->trapObjects->at(i)->render = false; //We don't want to render this with nonInstance rendering

				if (instanceMeshIndex.trapFireMesh == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.trapFireMesh = (int)i;
			}
		}

	}


#pragma endregion
}

XMFLOAT4X4 Graphics::CalculateWorldMatrix(XMFLOAT3 * position, XMFLOAT3 * rotation)
{
	DirectX::XMMATRIX scaleMatrix		 =  XMMatrixIdentity();

	//We convert from degrees to radians here. Before this point we work in degrees to make it easier for the programmer and user
	DirectX::XMMATRIX rotationMatrixX	 =  DirectX::XMMatrixRotationX(toRadian(rotation->x));
	DirectX::XMMATRIX rotationMatrixY	 =  DirectX::XMMatrixRotationY(toRadian(rotation->y));
	DirectX::XMMATRIX rotationMatrixZ	 =  DirectX::XMMatrixRotationZ(toRadian(rotation->z));

	//Create the rotation matrix
	DirectX::XMMATRIX rotationMatrix	 = DirectX::XMMatrixMultiply(rotationMatrixZ, rotationMatrixX);
	rotationMatrix						 = DirectX::XMMatrixMultiply(rotationMatrix, rotationMatrixY);

	//Intoduce the world matrix, multiply rotation and scale. (world translation comes later)
	DirectX::XMMATRIX world				 = DirectX::XMMatrixMultiply(rotationMatrix, scaleMatrix);


	//Create the world translation matrix
	DirectX::XMMATRIX translationMatrix  = DirectX::XMMatrixTranslation(position->x, position->y, position->z);


	//Multiply the (scale*rotation) matrix with the world translation matrix
	world								 = DirectX::XMMatrixMultiply(world, translationMatrix);
	world								 = XMMatrixTranspose(world);

	XMFLOAT4X4 toReturn;

	XMStoreFloat4x4(&toReturn, world);

	return toReturn;
}

XMFLOAT4X4 Graphics::CalculateWorldMatrix(XMFLOAT3 * position, XMFLOAT3 * rotation, XMFLOAT3 * scale)
{
	DirectX::XMMATRIX scaleMatrix	  = XMMatrixScaling(scale->x,scale->y,scale->z);

	//We convert from degrees to radians here. Before this point we work in degrees to make it easier for the programmer and user
	DirectX::XMMATRIX rotationMatrixX = DirectX::XMMatrixRotationX(toRadian(rotation->x));
	DirectX::XMMATRIX rotationMatrixY = DirectX::XMMatrixRotationY(toRadian(rotation->y));
	DirectX::XMMATRIX rotationMatrixZ = DirectX::XMMatrixRotationZ(toRadian(rotation->z));

	//Create the rotation matrix
	DirectX::XMMATRIX rotationMatrix  = DirectX::XMMatrixMultiply(rotationMatrixZ, rotationMatrixX);
	rotationMatrix					  = DirectX::XMMatrixMultiply(rotationMatrix, rotationMatrixY);

	//Intoduce the world matrix, multiply rotation and scale. (world translation comes later)
	DirectX::XMMATRIX world			  = DirectX::XMMatrixMultiply(rotationMatrix, scaleMatrix);


	//Create the world translation matrix
	DirectX::XMMATRIX translationMatrix = DirectX::XMMatrixTranslation(position->x, position->y, position->z);


	//Multiply the (scale*rotation) matrix with the world translation matrix
	world = DirectX::XMMatrixMultiply(world, translationMatrix);
	world = XMMatrixTranspose(world);

	XMFLOAT4X4 toReturn;

	XMStoreFloat4x4(&toReturn, world);

	return toReturn;
}


HRESULT Graphics::CreateDirect3DContext()
{

	//Swap chain description
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = (UINT)WIN_WIDTH;
	scd.BufferDesc.Height = (UINT)WIN_HEIGHT;
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_UNORDERED_ACCESS;
	scd.OutputWindow = *wndHandle;
	scd.SampleDesc.Count = 1;
	scd.Windowed = WINDOWED;
	scd.BufferDesc.RefreshRate.Numerator = FPS_CAP; //fps cap
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&this->gSwapChain,
		&this->gDevice,
		NULL,
		&this->gDeviceContext);

	if (FAILED(hr))
	{

		MessageBox(*wndHandle, L"Failed to create Swap Chain", L"Error", MB_ICONERROR | MB_OK);
		return hr;
	}



	if (DEBUG == 2)
	{
		hr = gDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);
		if (FAILED(hr))MessageBox(*wndHandle, L"ERROR INITIALIZING DEBUG", L"Error", MB_ICONERROR | MB_OK); 

	}



	//Here goes depth buffer
	D3D11_TEXTURE2D_DESC desc;

	desc.Width = (UINT)WIN_WIDTH;
	desc.Height = (UINT)WIN_HEIGHT;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	hr = gDevice->CreateTexture2D(&desc, 0, &depthBuffer);

	hr = gDevice->CreateDepthStencilView(depthBuffer, 0, &depthStencilView);

	//Create depth state
	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //Default
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS; //Default

	gDevice->CreateDepthStencilState(&dssDesc, &depthState);




	if (SUCCEEDED(hr))
	{
		ID3D11Texture2D* pBackBuffer = nullptr;

	
		this->gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);


		hr = this->gDevice->CreateRenderTargetView(pBackBuffer, NULL, &this->gBackBufferRTV);
		if (FAILED(hr))
		{

			MessageBox(*wndHandle, L"FAILED to create Backbuffer RTV", L"Error", MB_ICONERROR | MB_OK);
			return hr;
		}
		


		/*

		D3D11_UNORDERED_ACCESS_VIEW_DESC UAVdesc; //return to this when implementing compute shaders

		ZeroMemory(&UAVdesc, sizeof(UAVdesc));
		UAVdesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		UAVdesc.Buffer.FirstElement = 0;
		UAVdesc.Format = DXGI_FORMAT_UNKNOWN;
		UAVdesc.Buffer.NumElements = WINDOW_WIDTH * WINDOW_HEIGHT;*/



		hr = this->gDevice->CreateUnorderedAccessView(pBackBuffer, nullptr, &gBackBufferUAV);

		if (FAILED(hr))
		{

			MessageBox(*wndHandle, L"Failed to create UAV", L"Error", MB_ICONERROR | MB_OK);
			return hr;
		}


		hr = this->gDevice->CreateShaderResourceView(pBackBuffer, nullptr, &BackBufferTexture);

		if (FAILED(hr))
		{

			MessageBox(*wndHandle, L"FAILED to create Backbuffer SRV", L"Error", MB_ICONERROR | MB_OK);
			return hr;
		}


		pBackBuffer->Release();

		this->gDeviceContext->OMSetRenderTargets(1, &this->gBackBufferRTV, depthStencilView);

	}

	return hr;

}




#pragma region QueueRender functions

void Graphics::QueueRender(RenderInfoObject *object)
{
	this->gameObjects->push_back(object);
}

void Graphics::QueueRender(RenderInfoUI * object)
{
	this->uiObjects->push_back(object);
}

void Graphics::QueueRender(RenderInfoEnemy * object)
{
	this->enemyObjects->push_back(object);
}

void Graphics::QueueRender(RenderInfoChar * object)
{
	this->charObjects->push_back(object);
}

void Graphics::QueueRender(RenderInfoTrap * object)
{
	this->trapObjects->push_back(object);
}


Graphics * Graphics::GetInstance()
{
	static Graphics instance;
	return &instance;
}

XMFLOAT3 Graphics::GetPlayerDirection(XMFLOAT2 mousePos,XMFLOAT3 playerPos)
{
	//Here we do a picking algorithm
	//We get the mouse position in NDC
	//We convert it to world space. 
	//Then get a vector to be used as direction vector




	//We need
	// inverse view matrix
	// inverse projection matrix
	
	//Calculate mouse position in NDC space
	float vx = ((2.0f *  mousePos.x) / (float)WIN_WIDTH - 1.0f);
	float vy = ((2.0f * -mousePos.y) / (float)WIN_HEIGHT + 1.0f);

	XMVECTOR rayOrigin			= XMVectorSet(vx, vy, 0.0f, 1.0f);
	XMVECTOR rayDir				= rayOrigin;

	XMFLOAT3 unPack;
	XMStoreFloat3(&unPack, rayOrigin);
	rayDir						= XMVectorSet(unPack.x, unPack.y, 1.0f, 1.0f);

	XMMATRIX viewInverse;
	renderer->GetInverseViewMatrix( viewInverse );

	XMMATRIX projInverse;
	renderer->GetInverseProjectionMatrix( projInverse );


	XMMATRIX combinedInverse	= XMMatrixMultiply(projInverse, viewInverse);

	XMVECTOR rayPosInWorld		= XMVector3TransformCoord( rayOrigin, combinedInverse);
	XMVECTOR rayDirInWorld		= XMVector3TransformCoord( rayDir,    combinedInverse);
	rayDirInWorld				= XMVector3Normalize( rayDirInWorld - rayPosInWorld );

	float t						= 0.0f;
	XMVECTOR planeNormal		= XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	XMVECTOR result				= -( XMVector3Dot(rayPosInWorld, planeNormal)) / (XMVector3Dot(rayDirInWorld, planeNormal));

	XMStoreFloat(&t, result);	
	XMVECTOR intersection		= XMVectorAdd(rayPosInWorld, rayDirInWorld * t);
	
	XMStoreFloat4(&this->mouseWorldPos, intersection);
	this->renderer->SetMouseWorldPos(mouseWorldPos);

	XMVECTOR playerToCursor		= XMVectorSubtract(intersection, XMLoadFloat3(&XMFLOAT3(playerPos.x, 1.0f, playerPos.z)));
	XMStoreFloat3(&unPack, playerToCursor);
	
	playerToCursor				= XMVector3Normalize(XMVectorSet(unPack.x, 0.0f, unPack.z, 0.0f));
	

	
	XMFLOAT3 toReturn;
	XMStoreFloat3(&toReturn, playerToCursor);



	return toReturn;
}

#pragma endregion