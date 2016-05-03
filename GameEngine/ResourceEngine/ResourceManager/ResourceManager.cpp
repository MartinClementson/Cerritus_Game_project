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
	brfImporterHandler->LoadFile("models/Scene2.BRF", true, true, true);
	brfImporterHandler->LoadFile("models/quadBullet.BRF", true, true, true);
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
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
		MeshEnum meshType = object->object;
		meshManager		->GetMeshRenderInfo( &meshType, &currentMesh ); //Get the mesh data
		materialManager ->GetMaterialRenderInfo (&currentMesh );	    //Get the material data
	
	
		return &currentMesh;
		
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoUI * object)
	{
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoEnemy * object)
	{
		currentMesh = RenderInstructions();
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
		MeshEnum meshType = MeshEnum::ENEMY_1;//temporary

		if (meshType == MeshEnum::ENEMY_1 && gbufferPass == true)
			shaderManager->SetActiveShader(Shaders::GBUFFER_SHADER_INSTANCED);
		
		else if (shadowPass)
			shaderManager->SetActiveShader(Shaders::SHADOW_SHADER_INSTANCED);
		
		


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
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
 		MeshEnum meshType = object->object;
		
		meshManager->GetMeshRenderInfo(&meshType, &currentMesh);
	
		return &currentMesh;
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
