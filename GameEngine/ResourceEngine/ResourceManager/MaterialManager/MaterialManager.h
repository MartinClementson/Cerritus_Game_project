#pragma once
#include "../../../Enumerations/Enumerations.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../Structs/DataTypes.h"
#include "../TextureManager/TextureManager.h"

class MaterialManager
{
private:
	std::vector<Material>* materials;
	TextureManager* textureManager;
public:
	MaterialManager();
	~MaterialManager();
	void Initialize(ID3D11Device* gDevice);
	void Release();
	
	bool CompareMaterialsAt(importedMaterial* import, unsigned int materialID);
	bool CompareImportMaterials(importedMaterial* import);
	void addMaterials(std::vector<importedMaterial>* import);
	void GetMaterialRenderInfo(RenderInstructions * toRender);
	//RenderInstructions* GetMaterialRenderInfo(unsigned int materialID);
	//RenderInstructions* GetMaterialRenderInfo(std::string materialName);
};