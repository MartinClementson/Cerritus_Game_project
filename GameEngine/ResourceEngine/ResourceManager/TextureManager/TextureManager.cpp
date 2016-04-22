#include "TextureManager.h"
void TextureManager::Initialize()
{
}

void TextureManager::Release()
{
}

int TextureManager::GetDiffuseID(std::string diffuseTex)
{
	if (diffuseTex == "")
		return -1;
	if (this->diffuseTex.size() == 0)
	{
		this->diffuseTex.push_back(diffuseTex);
		return 0;
	}
	else
	{
		for (unsigned int i = 0; i < this->diffuseTex.size(); i++)
		{
			if (this->diffuseTex.at(i) == diffuseTex)
				return i;
		}
	}
	this->diffuseTex.push_back(diffuseTex);
	return (int)(this->diffuseTex.size() - 1);
}

int TextureManager::GetNormalID(std::string normalTex)
{
	if (normalTex == "")
		return -1;
	if (this->normalTex.size() == 0)
	{
		this->normalTex.push_back(normalTex);
		return 0;
	}
	else
	{
		for (unsigned int i = 0; i < this->normalTex.size(); i++)
		{
			if (this->normalTex.at(i) == normalTex)
				return i;
		}
	}
	this->normalTex.push_back(normalTex);
	return (int)(this->normalTex.size() - 1);
}

int TextureManager::GetSpecularID(std::string specularTex)
{
	if (specularTex == "")
		return -1;
	if (this->specularTex.size() == 0)
	{
		this->specularTex.push_back(specularTex);
		return 0;
	}
	else
	{
		for (unsigned int i = 0; i < this->specularTex.size(); i++)
		{
			if (this->specularTex.at(i) == specularTex)
				return i;
		}
	}
	this->specularTex.push_back(specularTex);
	return (int)(this->specularTex.size() - 1);
}

int TextureManager::GetGlowID(std::string glowTex)
{
	if (glowTex == "")
		return -1;
	if (this->glowTex.size() == 0)
	{
		this->glowTex.push_back(glowTex);
		return 0;
	}
	else
	{
		for (unsigned int i = 0; i < this->glowTex.size(); i++)
		{
			if (this->glowTex.at(i) == glowTex)
				return i;
		}
	}
	this->glowTex.push_back(glowTex);
	return (int)(this->glowTex.size() - 1);
}

int TextureManager::FindDiffuseID(std::string diffuseTex)
{
	for (unsigned int i = 0; i < this->diffuseTex.size(); i++)
	{
		if (this->diffuseTex.at(i) == diffuseTex)
			return i;
	}
	return -1;
}

int TextureManager::FindNormalID(std::string normalTex)
{
	for (unsigned int i = 0; i < this->normalTex.size(); i++)
	{
		if (this->normalTex.at(i) == normalTex)
			return i;
	}
	return -1;
}

int TextureManager::FindSpecularID(std::string specularTex)
{
	for (unsigned int i = 0; i < this->specularTex.size(); i++)
	{
		if (this->specularTex.at(i) == specularTex)
			return i;
	}
	return -1;
}

int TextureManager::FindGlowID(std::string glowTex)
{
	for (unsigned int i = 0; i < this->glowTex.size(); i++)
	{
		if (this->glowTex.at(i) == glowTex)
			return i;
	}
	return -1;
}

ID3D11ShaderResourceView * TextureManager::GetDiffuseTexture(int diffuseID)
{
	if (diffuseID == -1)
		return nullptr;

}

ID3D11ShaderResourceView * TextureManager::GetNormalTexture(int normalID)
{
	if (normalID == -1)
		return nullptr;
}

ID3D11ShaderResourceView * TextureManager::GetSpecularTexture(int specularID)
{
	if (specularID == -1)
		return nullptr;
}

ID3D11ShaderResourceView * TextureManager::GetGlowTexture(int glowID)
{
	if (glowID == -1)
		return nullptr;
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}
