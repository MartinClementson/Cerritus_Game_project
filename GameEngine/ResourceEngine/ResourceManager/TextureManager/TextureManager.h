#pragma once
#include "../../ObjectNode/Mesh/Mesh.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../Structs/DataTypes.h"
#include "../TextureManager/TextureManager.h"
#include "TextureResource\TextureResource.h"
class TextureManager
{
private:
	std::vector<TextureResource>* diffuseTextures;
	std::vector<TextureResource>* normalTextures;
	std::vector<TextureResource>* specularTextures;
	std::vector<TextureResource>* glowTextures;
public:
	void Initialize();
	void Release();

	TextureManager();
	~TextureManager();
};