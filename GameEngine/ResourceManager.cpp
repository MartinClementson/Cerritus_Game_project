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

void ResourceManager::Initialize()
{
	
}

void ResourceManager::Release()
{
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

#pragma endregion
