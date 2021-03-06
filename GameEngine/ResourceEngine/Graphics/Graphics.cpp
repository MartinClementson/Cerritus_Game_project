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
	if (gameObjects  != nullptr)
		delete gameObjects;
	if (charObjects  != nullptr)
		delete charObjects;
	if (uiObjects	 != nullptr)
		delete uiObjects;
	if (enemyObjects != nullptr)
		delete enemyObjects;
	if (trapObjects  != nullptr)
		delete trapObjects;
	if (shadowBuffer != nullptr)
		delete shadowBuffer;
	if (renderer	 != nullptr)
		delete renderer;
	if (gBuffer		 != nullptr)
		delete gBuffer;

	if (instancedWorldDataPerFrame != nullptr)
	{
		for (size_t i = 0; i < INSTANCED_WORLD_BUFFER_AMOUNT; i++)
			delete instancedWorldDataPerFrame[i];
	}

	if (billBoardArray != nullptr)
	{
			for (size_t i = 0; i < BILLBOARDED_ARRAYS; i++)
				delete billBoardArray[i];
			
	}
	delete instancedAnimationDataPerFrame;
	

	
}

void Graphics::Initialize(HWND * window)
{
	HRESULT hr;
	this->wndHandle  = window;

	hr				 = CreateDirect3DContext();
	antTweakBar = AntTweakBar::GetInstance();
	antTweakBar->Initialize(gDevice);
	//antTweakBar->addSlider("AnimSpeed", animationSpeed);
	//antTweakBar->addSlider("Animation", animation);
	

	gameObjects		 = new std::vector<RenderInfoObject*>;
	charObjects		 = new std::vector<RenderInfoChar*>;
	uiObjects		 = new std::vector<RenderInfoUI*>;
	enemyObjects	 = new std::vector<RenderInfoEnemy*>;
	trapObjects		 = new std::vector<RenderInfoTrap*>;

	instancedAnimationDataPerFrame					 = new InstancedAnimationData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[ENEMY_1_INSTANCED]    = new InstancedData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[ENEMY_2_INSTANCED]	 = new InstancedData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[PROJECTILE_INSTANCED] = new InstancedData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED]	 = new InstancedData[MAX_INSTANCED_GEOMETRY];
	instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED]	 = new InstancedData[MAX_INSTANCED_GEOMETRY];
	
	billBoardArray[PROJECTILE_BILLBOARD]			 = new BillboardData[MAX_BILLBOARDED_GEOMETRY];
	billBoardArray[HEALTH_BAR_BILLBOARD]			 = new BillboardData[MAX_BILLBOARDED_GEOMETRY];
	billBoardArray[PICKUP_HEALTH_BILLBOARD]			 = new BillboardData[MAX_BILLBOARDED_GEOMETRY];
	billBoardArray[PICKUP_WEAPON_BILLBOARD]			 = new BillboardData[MAX_BILLBOARDED_GEOMETRY];
	
	memset(billBoardArray[PROJECTILE_BILLBOARD],	  0, sizeof(billBoardArray[PROJECTILE_BILLBOARD]));
	memset(billBoardArray[HEALTH_BAR_BILLBOARD],      0, sizeof(billBoardArray[HEALTH_BAR_BILLBOARD]));

	memset(billBoardArray[PICKUP_HEALTH_BILLBOARD], 0, sizeof(billBoardArray[PICKUP_HEALTH_BILLBOARD]));
	memset(billBoardArray[PICKUP_WEAPON_BILLBOARD], 0, sizeof(billBoardArray[PICKUP_WEAPON_BILLBOARD]));



	memset(instancesToRender, 0, sizeof(instancesToRender)); //reset instances to render amount
	memset(billboardsToRender, 0, sizeof(billboardsToRender));
	renderer = new Renderer();
	renderer->Initialize(gDevice,this->gDeviceContext);
	
	gBuffer = new Gbuffer();
	gBuffer->Initialize(this->gDevice,this->gDeviceContext);

	shadowBuffer = new ShadowBuffer();
	shadowBuffer->Initialize(this->gDevice, this->gDeviceContext);



#pragma region Create three temporary blendshape animations

	XMFLOAT3 pos								    = XMFLOAT3(5.0f,5.0f, 0.0f);
	XMFLOAT3 rotation							    = XMFLOAT3(0.0f, 180.0f, 0.0f);
	instancedAnimationDataPerFrame[0].animation		= 0;
	instancedAnimationDataPerFrame[0].animationTime = 0;
	instancedAnimationDataPerFrame[0].worldMatrix   = CalculateWorldMatrix(&pos, &rotation);


	pos.x += 10;
	//rotation.y = 180.0f;
	instancedAnimationDataPerFrame[1].animation		= 1;
	instancedAnimationDataPerFrame[1].animationTime = 0;
	instancedAnimationDataPerFrame[1].worldMatrix   = CalculateWorldMatrix(&pos, &rotation);


	pos.x -= 20;
	rotation.y = 45.0f;
	instancedAnimationDataPerFrame[2].animation		= 2;
	instancedAnimationDataPerFrame[2].animationTime = 0;
	instancedAnimationDataPerFrame[2].worldMatrix = CalculateWorldMatrix(&pos, &rotation);


#pragma endregion
}

void Graphics::Update(double deltaTime)
{
	renderer->Update(deltaTime);
}

void Graphics::Release()
{

#pragma region Release custom classes

	renderer->Release();
	antTweakBar->Release();
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
	//while (gDevice->Release() > 0);
	SAFE_RELEASE(gDevice);

	
}

void Graphics::Render() //manage RenderPasses here
{



	if (charObjects->size() > 0)
		
		renderer->UpdateCamera(charObjects->at(0)->position);


	CullGeometry();									 //Remove geometry out of view

	SetShadowViewPort();

	shadowBuffer->ClearShadowGbuffer();

	shadowBuffer->ShadowSetToRender();

	renderer->SetShadowPass(true);

	this->RenderScene();							//Render shadowPass

	gBuffer->SetToRender(depthStencilView);	

	shadowBuffer->ShadowSetToRead();

	renderer->SetShadowPass(false);

	SetViewPort();

	//Set The gbuffer pass
	this->renderer->SetGbufferPass(true);



	if (instancesToRender[ENEMY_1_INSTANCED] > 0)
	{

		renderer->RenderInstanced(this->enemyObjects->at(instanceMeshIndex.enemy1Mesh),
			instancedAnimationDataPerFrame, instancesToRender[ENEMY_1_INSTANCED]);
	}
	RenderScene();									//Render to the gBuffer
													//Set the gBuffer as a subResource, send in the new RenderTarget
	gBuffer->SetToRead(gBackBufferRTV); 
	
	//blurpass
	this->renderer->RenderBlurPass(this->gBuffer->GetBlurUAV(), this->gBuffer->GetGlowSRV()); //blur the glow map

	this->renderer->RenderFinalPass();

	for (unsigned int i = 0; i < uiObjects->size(); i++)
		renderer->Render(uiObjects->at(i));
	
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
	std::vector<RenderInstructions>* tempInfo = new std::vector<RenderInstructions>;						//TEMPORARY
													//TEMPORARY
	this->renderer->Render(tempInfo);				//TEMPORARY
	delete tempInfo;
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
   		renderer->RenderBillBoard(
			this->gameObjects->at(instanceMeshIndex.projectileMesh),
			billBoardArray[PROJECTILE_BILLBOARD],
			instancesToRender[PROJECTILE_INSTANCED]);
	}
	////Render instanced enemies
	if (instancesToRender[ENEMY_2_INSTANCED] > 0)
	{
		renderer->RenderInstanced(this->enemyObjects->at(instanceMeshIndex.enemy2Mesh ),
			instancedWorldDataPerFrame[ ENEMY_2_INSTANCED ], instancesToRender[ ENEMY_2_INSTANCED ]);
	}

	if (billboardsToRender[HEALTH_BAR_BILLBOARD] > 0)
	{

		////////////BILLBOARD RENDERING
		renderer->RenderBillBoard(
			nullptr,
			billBoardArray    [HEALTH_BAR_BILLBOARD],
			billboardsToRender[HEALTH_BAR_BILLBOARD]);
	}

	if (billboardsToRender[PICKUP_HEALTH_BILLBOARD] > 0)
	{

		////////////BILLBOARD RENDERING
		renderer->RenderBillBoard(
			this->gameObjects->at(instanceMeshIndex.pickupHealth),
			billBoardArray[PICKUP_HEALTH_BILLBOARD],
			billboardsToRender[PICKUP_HEALTH_BILLBOARD]);
	}

	if (billboardsToRender[PICKUP_WEAPON_BILLBOARD] > 0)
	{

		////////////BILLBOARD RENDERING
		renderer->RenderBillBoard(
			this->gameObjects->at(instanceMeshIndex.pickupWeapon),
			billBoardArray[PICKUP_WEAPON_BILLBOARD],
			billboardsToRender[PICKUP_WEAPON_BILLBOARD]);
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

	



}

void Graphics::FinishFrame() // this one clears the graphics for this frame. So that it can start a new cycle next frame
{


	gBuffer->ClearGbuffer();

	this->renderer->SetGbufferPass(false);


	gameObjects  ->clear(); //clear the queue
	charObjects  ->clear();	//clear the queue
	enemyObjects ->clear();	//clear the queue
	trapObjects	 ->clear();	//clear the queue
	uiObjects	 ->clear();	//clear the queue
	
	memset(instancedWorldDataPerFrame[ENEMY_1_INSTANCED],    0, sizeof(instancedWorldDataPerFrame[ENEMY_1_INSTANCED]   ));	 //reset instance array
	memset(instancedWorldDataPerFrame[ENEMY_2_INSTANCED],	 0, sizeof(instancedWorldDataPerFrame[ENEMY_2_INSTANCED]));		 //reset instance array
	memset(instancedWorldDataPerFrame[PROJECTILE_INSTANCED], 0, sizeof(instancedWorldDataPerFrame[PROJECTILE_INSTANCED]));   //reset instance array
	memset(instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED],  0, sizeof(instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED]));	 //reset instance array
	memset(instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED],  0, sizeof(instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED]));	 //reset instance array

	memset(billBoardArray[PROJECTILE_BILLBOARD],    0, sizeof(billBoardArray[PROJECTILE_BILLBOARD]));
	memset(billBoardArray[HEALTH_BAR_BILLBOARD],    0, sizeof(billBoardArray[HEALTH_BAR_BILLBOARD]));
	memset(billBoardArray[PICKUP_HEALTH_BILLBOARD], 0, sizeof(billBoardArray[PICKUP_HEALTH_BILLBOARD]));
	memset(billBoardArray[PICKUP_WEAPON_BILLBOARD], 0, sizeof(billBoardArray[PICKUP_WEAPON_BILLBOARD]));
	
	

	memset(instancedAnimationDataPerFrame, 0, sizeof(instancedAnimationDataPerFrame));
	memset(instancesToRender,  0, sizeof(instancesToRender)); //reset instances to render amount
	memset(billboardsToRender, 0, sizeof(billboardsToRender));

	instanceMeshIndex.Reset();

	antTweakBar->Update();

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
	unsigned int	 healerIndex		 = 0;
	unsigned int	 healthBarIndex		 = 0;
	unsigned int	 bearTrapIndex		 = 0;
	unsigned int	 fireTrapIndex		 = 0;
	unsigned int	 weaponPickupIndex   = 0;
	unsigned int	 healthPickupIndex   = 0;
#pragma region Cull enemy objects
	for (size_t i = 0; i < this->enemyObjects->size(); i++)
	{
		//Frustum culling
		if (renderer->FrustumCheck(enemyObjects->at(i)->position, enemyObjects->at(i)->radius + 10) == false)
		{	
			//If its not visible
			this->enemyObjects->at(i)->render = false;
			continue;
		}
		 
		//else {

			//if object is visible and is enemy_1_type
		//	this->instancedWorldDataPerFrame[ENEMY_1_INSTANCED][enemyIndex].worldMatrix = CalculateWorldMatrix(&this->enemyObjects->at(i)->position, &this->enemyObjects->at(i)->rotation);

		if (enemyObjects->at(i)->object == MeshEnum::ENEMY_1)
		{

			instancedAnimationDataPerFrame[enemyIndex].animation	 = this->enemyObjects->at(i)->enemyAnim;
			instancedAnimationDataPerFrame[enemyIndex].animationTime = (float)min(max(0.0f, this->enemyObjects->at(i)->animationTime),1.0);
			instancedAnimationDataPerFrame[enemyIndex].worldMatrix   = CalculateWorldMatrix(&this->enemyObjects->at(i)->position, &this->enemyObjects->at(i)->rotation);
			
			instancesToRender				[ENEMY_1_INSTANCED] += 1;
			enemyIndex										    += 1;
		}
		else
		{
			instancedWorldDataPerFrame[ENEMY_2_INSTANCED][healerIndex].worldMatrix = CalculateWorldMatrix(&this->enemyObjects->at(i)->position, &this->enemyObjects->at(i)->rotation);
			instancedWorldDataPerFrame[ENEMY_2_INSTANCED][healerIndex].glow = 0;
			instancesToRender[ENEMY_2_INSTANCED]				 += 1;
			healerIndex											 += 1;
			if (instanceMeshIndex.enemy2Mesh == -1) //if this is the first thing we found of that mesh, store the index.
				instanceMeshIndex.enemy2Mesh = (int)i;

		}

			this->enemyObjects->at(i)->render = false; //Remove this object from normal rendering, since we render instanced
				if (instanceMeshIndex.enemy1Mesh == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.enemy1Mesh = (int)i;

				if (enemyObjects->at(i)->showHealthBar)
				{
					billBoardArray	  [HEALTH_BAR_BILLBOARD][healthBarIndex].glow = 0;//(enemyObjects->at(i)->isBeingHealed == true) ? 1 : 0; //Funkar inte
					billBoardArray	  [HEALTH_BAR_BILLBOARD][healthBarIndex].direction  = XMFLOAT3(0.0f, 1.0f, 0.0f);
					billBoardArray	  [HEALTH_BAR_BILLBOARD][healthBarIndex].height		= 0.1f;
					billBoardArray	  [HEALTH_BAR_BILLBOARD][healthBarIndex].width		= 2.0f * enemyObjects->at(i)->normalizedHealthVal;
					billBoardArray	  [HEALTH_BAR_BILLBOARD][healthBarIndex].worldPos	= 

						XMFLOAT3(	enemyObjects->at(i)->position.x - (2.0f - (billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width)), 	   // pos. x - (2 - width)
									5.0f ,																									       //height of the healthbar. 0 == on ground
									enemyObjects->at(i)->position.z);																		       // pos z.
					


					if (enemyObjects->at(i)->isOnfire)
					{
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow = 1;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 1.0f;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.3f;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 0.0f;
					}
					else if (enemyObjects->at(i)->isSlowed)
					{
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow = 1;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 0.0f;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.75f;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 1.0f;
					}
					else
					{
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow	 = 0;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 1.0f;
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.0f + enemyObjects->at(i)->normalizedHealthVal - 0.2f;		// -0.2f is just to make the red appear sooner
						billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 0.0f;

					}
					
				
					billboardsToRender[HEALTH_BAR_BILLBOARD] += 1;
					healthBarIndex							 += 1;
				}
		//}
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
				billBoardArray[PROJECTILE_BILLBOARD][projectileIndex].direction = this->gameObjects->at(i)->direction;
				billBoardArray[PROJECTILE_BILLBOARD][projectileIndex].height	= 3.0f;
				billBoardArray[PROJECTILE_BILLBOARD][projectileIndex].width		= 0.15f;
				billBoardArray[PROJECTILE_BILLBOARD][projectileIndex].glow		= 1;
				billBoardArray[PROJECTILE_BILLBOARD][projectileIndex].worldPos  = this->gameObjects->at(i)->position + (this->gameObjects->at(i)->direction *(billBoardArray[PROJECTILE_BILLBOARD][projectileIndex].height * 0.9f)); // this is to make sure that if we made a long shot, (like a railgun) we wouldnt want halv of the shot texture behind the character

				instancesToRender[PROJECTILE_INSTANCED]  += 1;
				projectileIndex							 += 1;
				this->gameObjects->at(i)->render		  = false; //We don't want to render this with nonInstance rendering
				
				if (instanceMeshIndex.projectileMesh == -1) //if this is the first thing we found of that mesh, store the index.
      					instanceMeshIndex.projectileMesh = (int)i;
			}


			else if (this->gameObjects->at(i)->object == MeshEnum::PICKUP_WEAPON)
			{
				billBoardArray[PICKUP_WEAPON_BILLBOARD][weaponPickupIndex].color	 = XMFLOAT3(1.0f, 0.0f, 0.0f); //TEMP
				billBoardArray[PICKUP_WEAPON_BILLBOARD][weaponPickupIndex].direction = XMFLOAT3(0.0f, 0.5f, 0.5f);
				billBoardArray[PICKUP_WEAPON_BILLBOARD][weaponPickupIndex].height    = 2.0f;
				billBoardArray[PICKUP_WEAPON_BILLBOARD][weaponPickupIndex].width     = 2.0f;
				billBoardArray[PICKUP_WEAPON_BILLBOARD][weaponPickupIndex].worldPos = gameObjects->at(i)->position;
				billBoardArray[PICKUP_WEAPON_BILLBOARD][weaponPickupIndex].worldPos.y += 1.2f;
				this->gameObjects->at(i)->render = false; //We don't want to render this with nonInstance rendering
				billboardsToRender[PICKUP_WEAPON_BILLBOARD] += 1;
				weaponPickupIndex += 1;

				if (instanceMeshIndex.pickupWeapon == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.pickupWeapon = (int)i;
			
			}

			else if (this->gameObjects->at(i)->object == MeshEnum::PICKUP_HEAL)
			{
				
				billBoardArray[PICKUP_HEALTH_BILLBOARD][healthPickupIndex].color	 = XMFLOAT3(0.0f, 1.0f, 0.0f); //TEMP
				billBoardArray[PICKUP_HEALTH_BILLBOARD][healthPickupIndex].direction = XMFLOAT3(0.0f, 0.5f, 0.5f);
				billBoardArray[PICKUP_HEALTH_BILLBOARD][healthPickupIndex].height    = 2.0f;
				billBoardArray[PICKUP_HEALTH_BILLBOARD][healthPickupIndex].glow		 = 0;
				billBoardArray[PICKUP_HEALTH_BILLBOARD][healthPickupIndex].width     = 2.0f;
				billBoardArray[PICKUP_HEALTH_BILLBOARD][healthPickupIndex].worldPos  = gameObjects->at(i)->position;
				billBoardArray[PICKUP_HEALTH_BILLBOARD][healthPickupIndex].worldPos.y += 1.2f;
				this->gameObjects->at(i)->render = false; //We don't want to render this with nonInstance rendering
				billboardsToRender[PICKUP_HEALTH_BILLBOARD] += 1;
				healthPickupIndex += 1;

				if (instanceMeshIndex.pickupHealth == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.pickupHealth = (int)i;
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
		if (renderer->FrustumCheck(trapObjects->at(i)->position, 10.0f) == false)
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
				this->instancedWorldDataPerFrame[TRAP_BEAR_INSTANCED][bearTrapIndex].glow = (this->trapObjects->at(i)->glow == true) ? 1 : 0 ;
				instancesToRender[TRAP_BEAR_INSTANCED] += 1;
				bearTrapIndex += 1;
				this->trapObjects->at(i)->render = false; //We don't want to render this with nonInstance rendering

				if (instanceMeshIndex.trapBearMesh == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.trapBearMesh = (int)i;

				if (this->trapObjects->at(i)->normalizedReloadVal > 0.0f) // if the trap is being reloaded (Render it as a healthbar
				{
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow = 0;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].direction = XMFLOAT3(0.0f, 1.0f, 0.0f);
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].height    = 0.5f;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width	   = 4.0f * trapObjects->at(i)->normalizedReloadVal;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].worldPos  =
						XMFLOAT3(trapObjects->at(i)->position.x - (4.0f - (billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width)), 	   // pos. x - (2 - width)
							5.0f,																									       //height of the healthbar. 0 == on ground
							trapObjects->at(i)->position.z + 4);																		       // pos z.

					
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 1.0f - trapObjects->at(i)->normalizedReloadVal ;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.0f + trapObjects->at(i)->normalizedReloadVal;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 0.0f;
					billboardsToRender[HEALTH_BAR_BILLBOARD] += 1;
					healthBarIndex += 1;


				}

			}

			else if (this->trapObjects->at(i)->object == MeshEnum::TRAP_FIRE)
			{
				this->instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED][fireTrapIndex].worldMatrix = CalculateWorldMatrix(&this->trapObjects->at(i)->position, &this->trapObjects->at(i)->rotation);
				this->instancedWorldDataPerFrame[TRAP_FIRE_INSTANCED][fireTrapIndex].glow = (this->trapObjects->at(i)->glow == true) ? 1 : 0;
				instancesToRender[TRAP_FIRE_INSTANCED] += 1;
				fireTrapIndex += 1;
				this->trapObjects->at(i)->render = false; //We don't want to render this with nonInstance rendering

				if (instanceMeshIndex.trapFireMesh == -1) //if this is the first thing we found of that mesh, store the index.
					instanceMeshIndex.trapFireMesh = (int)i;

				if (this->trapObjects->at(i)->normalizedReloadVal > 0.0f) // if the trap is being reloaded (Render it as a healthbar)
				{
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow = 0;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].direction = XMFLOAT3(0.0f, 1.0f, 0.0f);
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].height = 0.5f;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width = 4.0f * trapObjects->at(i)->normalizedReloadVal;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].worldPos =
						XMFLOAT3(trapObjects->at(i)->position.x - (4.0f - (billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width)), 	   // pos. x - (2 - width)
							5.0f,																									       //height of the healthbar. 0 == on ground
							trapObjects->at(i)->position.z +2 );																		       // pos z.

					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 1.0f - trapObjects->at(i)->normalizedReloadVal;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.0f + trapObjects->at(i)->normalizedReloadVal;
					billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 0.0f;


					billboardsToRender[HEALTH_BAR_BILLBOARD] += 1;
					healthBarIndex += 1;


				}


			}
		}

	}

#pragma region Set up the healthbar for the player
	if (charObjects->size() > 0)
	{
		if (charObjects->at(0)->showHealthBar)
		{


			billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].direction = XMFLOAT3(0.0f, 1.0f, 0.0f);
			billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].height = 0.3f;
			billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width = 3.0f * charObjects->at(0)->normalizedHealthVal;
			billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].worldPos = 
				XMFLOAT3(charObjects->at(0)->position.x - (3.0f - (billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width)), 	   // pos. x - (2 - width)
					5.0f,																									       //height of the healthbar. 0 == on ground
					charObjects->at(0)->position.z + 2);																		       // pos z.
			billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color =XMFLOAT3( 0.0f,0.0f,0.0f);
			if (charObjects->at(0)->isOnfire)
			{
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow	 = 1;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 1.0f;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.3f;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 0.0f;
			}
			else if (charObjects->at(0)->isSlowed)
			{
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow = 1;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 0.0f;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.75f;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 1.0f;
			}
			else
			{
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow	 = 0;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 1.0f - charObjects->at(0)->normalizedHealthVal;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.0f + charObjects->at(0)->normalizedHealthVal;
				billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 0.0f;
			}



			billboardsToRender[HEALTH_BAR_BILLBOARD] += 1;
			healthBarIndex += 1;
		}


#pragma region Alternate Laser

		////this->instancedWorldDataPerFrame[PROJECTILE_INSTANCED][projectileIndex].worldMatrix = CalculateWorldMatrix(&this->gameObjects->at(i)->position, &this->gameObjects->at(i)->rotation);
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].direction = this->charObjects->at(0)->direction;
		//float x = XMVector3Length(XMLoadFloat3(&this->charObjects->at(0)->direction)).m128_f32[0];
		//

		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].height = x;
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].width = 0.05f;
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].glow = 1;
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].screenSpace = 0;
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].worldPos = this->charObjects->at(0)->position + (this->charObjects->at(0)->direction *(billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].height)); // this is to make sure that if we made a long shot, (like a railgun) we wouldnt want halv of the shot texture behind the character
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].worldPos.y = 5.0f;
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.x = 1.0f;
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.y = 0.0f;
		//billBoardArray[HEALTH_BAR_BILLBOARD][healthBarIndex].color.z = 0.0f;

		//

		//billboardsToRender[HEALTH_BAR_BILLBOARD] += 1;
		//healthBarIndex += 1;
#pragma endregion







	}

	


#pragma endregion





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

void Graphics::QueueRender(RenderInfoScene * object)
{
	this->sceneObjects->push_back(object);
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