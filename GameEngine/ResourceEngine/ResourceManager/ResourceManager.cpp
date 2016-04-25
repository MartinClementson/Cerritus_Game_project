#include "ResourceManager.h"

#define toRadian(degrees) ((degrees)* (XM_PI/180.0f))

ResourceManager::ResourceManager()
{
	meshManager = new MeshManager();
	shaderManager = new ShaderManager();
	brfImporterHandler = new BRFImporterHandler();

}


ResourceManager::~ResourceManager()
{
	delete meshManager;
	delete shaderManager;
	delete brfImporterHandler;
}

void ResourceManager::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	shaderManager->Initialize(gDevice, gDeviceContext);
	meshManager->Initialize(gDevice, gDeviceContext);
	brfImporterHandler->Initialize(this->meshManager);
	brfImporterHandler->LoadFile("MainChar.BRF", true, true, true);
	brfImporterHandler->LoadFile("EnemyChar.BRF", true, true, true);
	brfImporterHandler->LoadFile("FireTrap.BRF", true, true, true);
	brfImporterHandler->LoadFile("BearTrap.BRF", true, true, true);
}

void ResourceManager::Release()
{
	this->shaderManager->Release();
	this->meshManager->Release();
	this->brfImporterHandler->Release();

}


#pragma region GetRenderInfo() overloads

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoObject * object)
	{
		/*currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
		MeshEnum meshType = MeshEnum::TRAP_BEAR;
		
		meshManager->GetMeshRenderInfo(&meshType, &currentMesh);
		Shaders temp = PHONG_SHADER;
		this->shaderManager->SetActiveShader(&temp);
		return &currentMesh;*/
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoUI * object)
	{
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoEnemy * object)
	{
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
		MeshEnum meshType = MeshEnum::ENEMY_1;

		meshManager->GetMeshRenderInfo(&meshType, &currentMesh);
		Shaders temp = PHONG_SHADER;
		this->shaderManager->SetActiveShader(&temp);
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoChar * object)
	{

		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
		MeshEnum meshType = MeshEnum::MAIN_CHARACTER;

		meshManager->GetMeshRenderInfo(&meshType,&currentMesh);
		Shaders temp = PHONG_SHADER;
		this->shaderManager->SetActiveShader(&temp);
		return &currentMesh;


		
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoTrap * object)
	{
		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&object->position, &object->rotation);
 		MeshEnum meshType = object->object;
		
		meshManager->GetMeshRenderInfo(&meshType, &currentMesh);
		Shaders temp = PHONG_SHADER;
		this->shaderManager->SetActiveShader(&temp);
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetPlaceHolderMesh(XMFLOAT3 position)
	{
		////////////TEMPORARY////////////////////////////////
		
		static float rotation = 0;
		rotation += 0.1f;
		XMFLOAT3 tempRotation = XMFLOAT3(0.0, rotation, 0.0);
		////////////////////////////////////////////////////////////

		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&position, &tempRotation);


		meshManager->GetPlaceHolderMeshInfo(&currentMesh);
		Shaders temp = PHONG_SHADER;
		this->shaderManager->SetActiveShader(&temp);
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetPlaceHolderMesh(XMFLOAT3 position, XMFLOAT3 rotation)
	{
		

		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&position, &rotation);


		meshManager->GetPlaceHolderMeshInfo(&currentMesh);
		Shaders temp = PHONG_SHADER;
		this->shaderManager->SetActiveShader(&temp);
		return &currentMesh;
	}

	RenderInstructions * ResourceManager::GetPlaceHolderPlane()
	{


		////////////TEMPORARY////////////////////////////////
		XMFLOAT3 tempPos = XMFLOAT3(0.0f, 0.0f, -1.5f);
		
		XMFLOAT3 tempRotation = XMFLOAT3(0.0, 0.0, 0.0);
		////////////////////////////////////////////////////////////

		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&tempPos, &tempRotation);


		meshManager->GetPlaceHolderPlaneInfo(&currentMesh);
		Shaders temp = PHONG_SHADER;
		this->shaderManager->SetActiveShader(&temp);
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

#pragma endregion
