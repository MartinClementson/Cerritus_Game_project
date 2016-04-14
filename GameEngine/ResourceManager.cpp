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

