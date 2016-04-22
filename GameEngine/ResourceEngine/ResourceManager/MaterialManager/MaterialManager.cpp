#include "MaterialManager.h"

MaterialManager::~MaterialManager()
{
}

void MaterialManager::Initialize()
{
}

void MaterialManager::Release()
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
