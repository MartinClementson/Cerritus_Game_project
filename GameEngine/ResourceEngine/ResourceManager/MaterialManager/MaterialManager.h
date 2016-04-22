#pragma once
#include "../../ObjectNode/Mesh/Mesh.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../Structs/DataTypes.h"
#include "../TextureManager/TextureManager.h"

class MaterialManager
{
private:
		~MaterialManager();

		//std::vector<Material>* materials;
		//TextureManager* textureManager;
		TextureManager* textureManager;
public:
	void Initialize();
	void Release();

	void GetMaterialRenderInfo(RenderInstructions * toRender);
}