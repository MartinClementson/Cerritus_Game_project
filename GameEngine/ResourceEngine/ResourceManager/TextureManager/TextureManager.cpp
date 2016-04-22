#include "TextureManager.h"
void TextureManager::Initialize()
{
}

void TextureManager::Release()
{
}

int TextureManager::GetDiffuseID(std::string diffuseTex)
{
	if (this->diffuseTex.size == 0 && diffuseTex != "")
	{
		this->diffuseTex.push_back(diffuseTex);
		return 0;
	}
	else if (diffuseTex != "")
	{
		this->diffuseTex.push_back(diffuseTex);
		return (this->diffuseTex.size() - 1);
	}
	return -1;
}

int TextureManager::GetNormalID(std::string normalTex)
{
	if (this->normalTex.size == 0 && normalTex != "")
	{
		this->normalTex.push_back(normalTex);
		return 0;
	}
	else if (normalTex != "")
	{
		this->normalTex.push_back(normalTex);
		return (this->normalTex.size() - 1);
	}
	return -1;
}

int TextureManager::GetSpecularID(std::string specularTex)
{
	if (this->specularTex.size == 0 && specularTex != "")
	{
		this->specularTex.push_back(specularTex);
		return 0;
	}
	else if (specularTex != "")
	{
		this->specularTex.push_back(specularTex);
		return (this->specularTex.size() - 1);
	}
	return -1;
}

int TextureManager::GetGlowID(std::string glowTex)
{
	if (this->glowTex.size == 0 && glowTex != "")
	{
		this->glowTex.push_back(glowTex);
		return 0;
	}
	else if (glowTex != "")
	{
		this->glowTex.push_back(glowTex);
		return (this->glowTex.size() - 1);
	}
	return -1;
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}
