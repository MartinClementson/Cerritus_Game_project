#include "MaterialManager.h"

MaterialManager::MaterialManager()
{
	textureManager = new TextureManager;
	materials = nullptr;
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
	for (unsigned int i = 0; i < import->size(); i++)
	{
		if (materials != nullptr)
		{
			for (unsigned int j = 0; j < materials->size(); j++)
			{
				if (import->at(i).materialName == materials->at(j).materialName)
				{

				}
			}
		}
		else
		{
			Material tempMaterial;
			tempMaterial.materialName = import->at(i).materialName;
			tempMaterial.materialID = import->at(i).materialID;

			tempMaterial.diffuseValue = import->at(i).diffuseValue;
			tempMaterial.specularValue = import->at(i).specularValue;

			//getting the IDs for the textures
			tempMaterial.diffuse_ID = textureManager->GetDiffuseID(import->at(i).diffuseTex);
			tempMaterial.specular_ID = textureManager->GetSpecularID(import->at(i).specularTex);
			tempMaterial.normal_ID = textureManager->GetNormalID(import->at(i).normalTex);
			tempMaterial.glow_ID = textureManager->GetGlowID(import->at(i).glowTex);

			materials->push_back(tempMaterial);
		}
	}
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
