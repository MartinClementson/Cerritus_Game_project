#include "ResourceManager.h"

#define toRadian(degrees) ((degrees)* (XM_PI/180.0f))

ResourceManager::ResourceManager()
{
	meshManager = new MeshManager();
	shaderManager = new ShaderManager();

}


ResourceManager::~ResourceManager()
{
	delete meshManager;
	delete shaderManager;
}

void ResourceManager::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	shaderManager->Initialize(gDevice, gDeviceContext);
	meshManager->Initialize(gDevice, gDeviceContext);
}

void ResourceManager::Release()
{
	this->shaderManager->Release();
	this->meshManager->Release();

}


#pragma region GetRenderInfo() overloads

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoObject * object)
	{
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoUI * object)
	{
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoEnemy * object)
	{
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoChar * object)
	{
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetRenderInfo(RenderInfoTrap * object)
	{
		return nullptr;
	}

	RenderInstructions * ResourceManager::GetPlaceHolderMesh()
	{
		////////////TEMPORARY////////////////////////////////
		XMFLOAT3 tempPos = XMFLOAT3(0.0f, 0.0f, -1.5f);
		static float rotation = 0;
		rotation += 0.1f;
		XMFLOAT3 tempRotation = XMFLOAT3(0.0, rotation, 0.0);
		////////////////////////////////////////////////////////////

		currentMesh.worldBuffer.worldMatrix = CalculateWorldMatrix(&tempPos, &tempRotation);


		meshManager->GetPlaceHolderMeshInfo(&currentMesh);
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
