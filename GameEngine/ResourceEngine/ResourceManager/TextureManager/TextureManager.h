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
	std::vector<std::string> diffuseTex;
	std::vector<std::string> normalTex;
	std::vector<std::string> specularTex;
	std::vector<std::string> glowTex;

	std::vector<TextureResource>* diffuseTextures;
	std::vector<TextureResource>* normalTextures;
	std::vector<TextureResource>* specularTextures;
	std::vector<TextureResource>* glowTextures;
public:
	void Initialize();
	void Release();

	int GetDiffuseID(std::string diffuseTex);
	int GetNormalID(std::string normalTex);
	int GetSpecularID(std::string specularTex);
	int GetGlowID(std::string glowTex);
	TextureManager();
	~TextureManager();
};