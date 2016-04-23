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

bool MaterialManager::CompareImportMaterials(importedMaterial * import)
{
	for (unsigned int j = 0; j < materials->size(); j++)
	{
		if (import->materialName == materials->at(j).materialName)
		{
			if (materials->at(j).diffuse_ID == textureManager->FindDiffuseID(import->diffuseTex))
			{
				if (materials->at(j).normal_ID == textureManager->FindNormalID(import->normalTex))
				{
					if (materials->at(j).specular_ID == textureManager->FindSpecularID(import->specularTex))
					{
						if (materials->at(j).glow_ID == textureManager->FindGlowID(import->glowTex))
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void MaterialManager::Initialize(ID3D11Device* gDevice)
{
	textureManager->Initialize(gDevice);
}

void MaterialManager::Release()
{
	this->textureManager->Release();
}

void MaterialManager::addMaterials(std::vector<importedMaterial>* import)
{
	for (unsigned int i = 0; i < import->size(); i++)
	{
		if (materials != nullptr)
		{
			if (!CompareImportMaterials(&import->at(i)))
			{
				materials = new std::vector<Material>;
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
		else
		{
			materials = new std::vector<Material>;
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
	//toRender->diffuseMap = textureManager->GetDiffuseTexture(materials->at(toRender->materialID).diffuse_ID);
	toRender->diffuseMap = textureManager->GetDiffuseTexture(0);
}

//RenderInstructions * MaterialManager::GetMaterialRenderInfo(unsigned int materialID)
//{
//	return nullptr;
//}
//
//RenderInstructions * MaterialManager::GetMaterialRenderInfo(std::string materialName)
//{
//	return nullptr;
//}
