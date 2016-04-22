#pragma once
#include "../../ObjectNode/Mesh/Mesh.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../Structs/DataTypes.h"
#include "../TextureManager/TextureManager.h"

class MaterialManager
{
private:
	std::vector<Material>* materials;
	TextureManager* textureManager;
	bool CompareImportMaterials(importedMaterial* import);
public:
	MaterialManager();
	~MaterialManager();
	void Initialize(ID3D11Device* gDevice);
	void Release();
	
	void addMaterials(std::vector<importedMaterial>* import);
	void GetMaterialRenderInfo(RenderInstructions * toRender);
	//RenderInstructions* GetMaterialRenderInfo(unsigned int materialID);
	//RenderInstructions* GetMaterialRenderInfo(std::string materialName);
};