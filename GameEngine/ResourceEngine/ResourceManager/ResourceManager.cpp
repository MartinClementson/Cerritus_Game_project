#include "ResourceManager.h"

#define toRadian(degrees) ((degrees)* (XM_PI/180.0f))

ResourceManager::ResourceManager()
{
	meshManager = new MeshManager();
	shaderManager = new ShaderManager();
	brfImporterHandler = new BRFImporterHandler();
	materialManager = new MaterialManager();
}


ResourceManager::~ResourceManager()
{
	delete meshManager;
	delete shaderManager;
	delete brfImporterHandler;
	delete materialManager;
}

void ResourceManager::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	shaderManager->Initialize(gDevice, gDeviceContext);
	meshManager->Initialize(gDevice, gDeviceContext);
	materialManager->Initialize(gDevice);
	brfImporterHandler->Initialize(this->meshManager, this->materialManager);


	brfImporterHandler->LoadFile("models/player_Model.BRF", true, true, true);
	brfImporterHandler->LoadFile("models/enemy_0.BRF", true, true, true);
	brfImporterHandler->LoadFile("models/slow_Trap.BRF", true, true, true);
	brfImporterHandler->LoadFile("models/FireTrap.BRF", true, true, true);
	brfImporterHandler->LoadFile("models/BearTrap.BRF", true, true, true);
	brfImporterHandler->LoadFile("models/Scene2.BRF", true, true, true);
	brfImporterHandler->LoadFile("models/quadBullet.BRF", true, true, true);
	
	


	std::vector<importedMaterial> temp;
	importedMaterial ui;
	ui.materialName = "yo-gi-uh";
	ui.diffuseTex = "HUD.tif";
	ui.materialID = 9;
	
	temp.push_back(ui);

	materialManager->addMaterials(&temp);
	ui.materialName = "Menumaterial";
	ui.diffuseTex = "menu.png";
	ui.materialID = 10;
	
	temp.push_back(ui);

	materialManager->addMaterials(&temp);
	ui.materialName = "gameover";
	ui.diffuseTex = "GameOver.png";
	ui.materialID = 11;

	temp.push_back(ui);

	materialManager->addMaterials(&temp);
	ui.materialName = "pause";
	ui.diffuseTex = "PausUI.tif";
	ui.materialID = 12;
	temp.push_back(ui);

	materialManager->addMaterials(&temp);
	ui.materialName = "MenuExit";
	ui.diffuseTex = "ExitButtonMenu.png";
	ui.materialID = 13;
	temp.push_back(ui);

	materialManager->addMaterials(&temp);
	ui.materialName = "MenuNew";
	ui.diffuseTex = "NewGameMenu.png";
	ui.materialID = 14;
	temp.push_back(ui);

	materialManager->addMaterials(&temp);
	ui.materialName = "MenuControls";
	ui.diffuseTex = "ControlsMenuButton.png";
	ui.materialID = 15;
	temp.push_back(ui);

	materialManager->addMaterials(&temp);
	//materialManager->addMaterials(&temp);
	ui.materialName = "Controls";
	ui.diffuseTex = "Controls.png";
	ui.materialID = 16;
	temp.push_back(ui);

	//materialManager->addMaterials(&temp);
}

void ResourceManager::Release()
{
	this->shaderManager->Release();
	this->meshManager->Release();
	this->brfImporterHandler->Release();
	this->materialManager->Release();
}


#pragma region GetRenderInfo() overloads

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoObject * object)
	{
		currentMesh = RenderInstructions();
		MeshEnum meshType = object->object;


		

		if(meshType != MeshEnum::PROJECTILE_1)
			currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);


		meshManager		->GetMeshRenderInfo( &meshType, &currentMesh ); //Get the mesh data
		materialManager ->GetMaterialRenderInfo (&currentMesh );	    //Get the material data
	
	
		return &currentMesh;
		
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoUI * object)
	{
		currentUI = RenderInstructions();
		
		//currentUI.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->size, &object->position);
		Shaders tmp = UI_SHADER;
		UITextures uiType = object->object;
		this->shaderManager->SetActiveShader(tmp);
		meshManager->GetFullScreenQuadInfoUI(&uiType,&currentUI);
		materialManager->GetMaterialRenderInfo(&currentUI);
	
		return &currentUI;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoEnemy * object)
	{
		currentMesh							= RenderInstructions();
		MeshEnum meshType					= MeshEnum::ENEMY_1;//temporary

		if (     meshType == MeshEnum::ENEMY_1 && gbufferPass == true)
			shaderManager->SetActiveShader(Shaders::GBUFFER_SHADER_INSTANCED);
		
		else if (meshType == MeshEnum::ENEMY_1 && shadowPass  == true)
			shaderManager->SetActiveShader(Shaders::SHADOW_SHADER_INSTANCED);

		else
			currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
		
		


		meshManager->GetMeshRenderInfo(&meshType, &currentMesh);
		materialManager->GetMaterialRenderInfo(&currentMesh);
		
	
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoChar * object)
	{
		currentMesh = RenderInstructions();
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
		MeshEnum meshType = MeshEnum::MAIN_CHARACTER;





		meshManager->GetMeshRenderInfo(&meshType,&currentMesh);
		materialManager->GetMaterialRenderInfo(&currentMesh);
		
		

		return &currentMesh;


		
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoTrap * object)
	{
		currentMesh = RenderInstructions();
 		MeshEnum meshType = object->object;


		if (   meshType == MeshEnum::TRAP_BEAR && gbufferPass == true
			|| meshType == MeshEnum::TRAP_FIRE && gbufferPass == true)
				shaderManager->SetActiveShader(Shaders::GBUFFER_SHADER_INSTANCED);

		else if ( meshType == MeshEnum::TRAP_BEAR && shadowPass == true
				|| meshType == MeshEnum::TRAP_FIRE && shadowPass == true)
				shaderManager->SetActiveShader(Shaders::SHADOW_SHADER_INSTANCED);
		else
			currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);

		meshManager->GetMeshRenderInfo(&meshType, &currentMesh);
		materialManager->GetMaterialRenderInfo(&currentMesh);
		
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetAnimationRenderInfo(RenderInfoEnemy * object)
	{

		currentMesh = RenderInstructions();
		MeshEnum meshType = MeshEnum::ENEMY_1;//temporary

		shaderManager->SetActiveShader(Shaders::ANIMATION_SHADER);
		/*if (meshType == MeshEnum::ENEMY_1 && gbufferPass == true)
			shaderManager->SetActiveShader(Shaders::GBUFFER_SHADER_INSTANCED);

		else if (meshType == MeshEnum::ENEMY_1 && shadowPass == true)
			shaderManager->SetActiveShader(Shaders::SHADOW_SHADER_INSTANCED);*/

		

		//meshManager->GetMeshRenderInfo(&meshType, &currentMesh);

		meshManager->GetPlaceHolderMeshInfo(&currentMesh);
		//materialManager->GetMaterialRenderInfo(&currentMesh);


		return &currentMesh;

		return nullptr;
	}

	RenderInstructions * ResourceManager::GetPlaceHolderMesh(XMFLOAT3 position)
	{
		////////////TEMPORARY////////////////////////////////
		
		static float rotation = 0;
		rotation += 0.1f;
		XMFLOAT3 tempRotation = XMFLOAT3(0.0, rotation, 0.0);
		////////////////////////////////////////////////////////////
		currentMesh = RenderInstructions();
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&position, &tempRotation);


		meshManager->GetPlaceHolderMeshInfo(&currentMesh);
	
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetPlaceHolderMesh(XMFLOAT3 position, XMFLOAT3 rotation)
	{
		
		currentMesh = RenderInstructions();
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&position, &rotation);


		meshManager->GetPlaceHolderMeshInfo(&currentMesh);

	
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetPlaceHolderPlane()
	{

		currentMesh = RenderInstructions();
		////////////TEMPORARY////////////////////////////////
		XMFLOAT3 tempPos = XMFLOAT3(0.0f, 0.0f, -1.5f);
		
		XMFLOAT3 tempRotation = XMFLOAT3(0.0, 0.0, 0.0);
		////////////////////////////////////////////////////////////

		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&tempPos, &tempRotation);

		meshManager->GetPlaceHolderPlaneInfo(&currentMesh);



		return &currentMesh;
		
	}

	RenderInstructions * ResourceManager::GetFullScreenQuad()
	{
		currentMesh = RenderInstructions();
		
		this->shaderManager->SetActiveShader(FINAL_SHADER);
		meshManager->GetFullScreenQuadInfo(&currentMesh);

		return &currentMesh;
	}


	XMFLOAT4X4 ResourceManager::CalculateWorldMatrix(XMFLOAT3* position, XMFLOAT3* rotation)
	{
		DirectX::XMMATRIX scaleMatrix		 = XMMatrixIdentity();

		//We convert from degrees to radians here. Before this point we work in degrees to make it easier for the programmer and user
		DirectX::XMMATRIX rotationMatrixX	 = DirectX::XMMatrixRotationX(	toRadian(	rotation->x	)	);
		DirectX::XMMATRIX rotationMatrixY	 = DirectX::XMMatrixRotationY(	toRadian(	rotation->y	)	);
		DirectX::XMMATRIX rotationMatrixZ	 = DirectX::XMMatrixRotationZ(	toRadian(	rotation->z	)	);
		
		//Create the rotation matrix
		DirectX::XMMATRIX rotationMatrix	 = DirectX::XMMatrixMultiply( rotationMatrixZ, rotationMatrixX );
		rotationMatrix						 = DirectX::XMMatrixMultiply( rotationMatrix,  rotationMatrixY );

		//Intoduce the world matrix, multiply rotation and scale. (world translation comes later)
		DirectX::XMMATRIX world				 = DirectX::XMMatrixMultiply(rotationMatrix, scaleMatrix);


		//Create the world translation matrix
		DirectX::XMMATRIX translationMatrix = DirectX::XMMatrixTranslation( position->x, position->y, position->z );


		//Multiply the (scale*rotation) matrix with the world translation matrix
		world = DirectX::XMMatrixMultiply( world, translationMatrix );


		world = XMMatrixTranspose(world);

		XMFLOAT4X4 toReturn;

		XMStoreFloat4x4(&toReturn, world);

		return toReturn;
	}

	XMFLOAT4X4 ResourceManager::CalculateWorldMatrix(XMFLOAT3* position, XMFLOAT3* rotation, XMFLOAT3* scale)
	{
		return XMFLOAT4X4();
	}

	void ResourceManager::SetGbufferPass(bool x)
	{
		if (this->gbufferPass != x)
			this->gbufferPass = x;

		if (gbufferPass == true)
		{

			this->shaderManager->SetActiveShader(GBUFFER_SHADER);
			shadowPass = false;
		}
	}


	void ResourceManager::SetShadowPass(bool x)
	{
		if (this->shadowPass != x)
			this->shadowPass = x;
		if (shadowPass == true)
		{
			this->shaderManager->SetActiveShader(SHADOW_SHADER);
			gbufferPass = false;
		}
	}

	

#pragma endregion
