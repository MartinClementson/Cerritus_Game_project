#include "MaterialManager.h"

MaterialManager::MaterialManager()
{
	textureManager = new TextureManager;
}

MaterialManager::~MaterialManager()
{
	delete materials;
	delete textureManager;
}

void MaterialManager::Initialize()
{
}

void MaterialManager::Release()
{
}

void MaterialManager::addMaterials(std::vector<importedMaterial>* import)
{
}

void MaterialManager::GetMaterialRenderInfo(RenderInstructions * toRender)
{
}

RenderInstructions * MaterialManager::GetMaterialRenderInfo(unsigned int materialID)
{
	return nullptr;
}

RenderInstructions * MaterialManager::GetMaterialRenderInfo(std::string materialName)
{
	return nullptr;
}
