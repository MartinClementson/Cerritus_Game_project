#include "MaterialManager.h"

MaterialManager::MaterialManager()
{
	textureManager = new TextureManager;
	materials = new std::vector<Material>;;
}

MaterialManager::~MaterialManager()
{
	delete materials;
	delete textureManager;
}

bool MaterialManager::CompareMaterialsAt(importedMaterial * import, unsigned int materialID)
{
	if (import->materialName == materials->at(materialID).materialName)
	{
		if (materials->at(materialID).diffuse_ID == textureManager->FindDiffuseID(import->diffuseTex))
		{
			if (materials->at(materialID).normal_ID == textureManager->FindNormalID(import->normalTex))
			{
				if (materials->at(materialID).specular_ID == textureManager->FindSpecularID(import->specularTex))
				{
					if (materials->at(materialID).glow_ID == textureManager->FindGlowID(import->glowTex))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
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
		if (materials->size() > 0)
		{
			if (!CompareImportMaterials(&import->at(i)))
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
				materials->shrink_to_fit();
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
	toRender->diffuseMap = textureManager->GetDiffuseTexture(materials->at(toRender->materialID).diffuse_ID);
	toRender->normalMap = textureManager->GetNormalTexture(materials->at(toRender->materialID).normal_ID);
	toRender->specularMap = textureManager->GetSpecularTexture(materials->at(toRender->materialID).specular_ID);
	toRender->glowMap = textureManager->GetGlowTexture(materials->at(toRender->materialID).glow_ID);
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
