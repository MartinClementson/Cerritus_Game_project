#include "ResourceManager.h"



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
		meshManager->GetPlaceHolderMeshInfo(&currentMesh);
		return &currentMesh;
	}

#pragma endregion
