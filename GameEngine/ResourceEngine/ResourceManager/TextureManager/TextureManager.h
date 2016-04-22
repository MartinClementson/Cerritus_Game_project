#pragma once
#include "../../ObjectNode/Mesh/Mesh.h"
#include "../../../Enumerations/Enumerations.h"
#include "../../../Structs/RenderInfo.h"
#include "../../../Structs/DataTypes.h"
#include "../TextureManager/TextureManager.h"
#include "TextureResource\TextureResource.h"
#include "../../DirectXTK/Inc/WICTextureLoader.h"
class TextureManager
{
private:
	std::vector<std::string> diffuseTex;
	std::vector<std::string> normalTex;
	std::vector<std::string> specularTex;
	std::vector<std::string> glowTex;

	std::vector<ID3D11ShaderResourceView*> diffuseTextures;
	std::vector<ID3D11ShaderResourceView*> normalTextures;
	std::vector<ID3D11ShaderResourceView*> specularTextures;
	std::vector<ID3D11ShaderResourceView*> glowTextures;

	void AddDiffuseTexture(std::string diffuseTex);
	void AddNormalTexture(std::string diffuseTex);
	void AddSpecularTexture(std::string diffuseTex);
	void AddGlowTexture(std::string diffuseTex);

public:
	void Initialize();
	void Release();

	int GetDiffuseID(std::string diffuseTex);
	int GetNormalID(std::string normalTex);
	int GetSpecularID(std::string specularTex);
	int GetGlowID(std::string glowTex);

	int FindDiffuseID(std::string diffuseTex);
	int FindNormalID(std::string normalTex);
	int FindSpecularID(std::string specularTex);
	int FindGlowID(std::string glowTex);

	ID3D11ShaderResourceView* GetDiffuseTexture(int diffuseID);
	ID3D11ShaderResourceView* GetNormalTexture(int normalID);
	ID3D11ShaderResourceView* GetSpecularTexture(int specularID);
	ID3D11ShaderResourceView* GetGlowTexture(int glowID);
	TextureManager();
	~TextureManager();
};