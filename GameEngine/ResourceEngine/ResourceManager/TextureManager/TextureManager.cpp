#include "TextureManager.h"

void TextureManager::Initialize(ID3D11Device* gDevice)
{
	this->gDevice = gDevice;
	CoInitialize((LPVOID)0);
}

void TextureManager::Release()
{
	for (unsigned int i = 0; i < diffuseTextures.size(); i++)
		SAFE_RELEASE(*diffuseTextures.at(i));
	for (unsigned int i = 0; i < normalTextures.size(); i++)
		SAFE_RELEASE(*normalTextures.at(i));
	for (unsigned int i = 0; i < specularTextures.size(); i++)
		SAFE_RELEASE(*specularTextures.at(i));
	for (unsigned int i = 0; i < glowTextures.size(); i++)
		SAFE_RELEASE(*glowTextures.at(i));
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	for (unsigned int i = 0; i < diffuseTextures.size(); i++)
		delete diffuseTextures.at(i);
	for (unsigned int i = 0; i < normalTextures.size(); i++)
		delete normalTextures.at(i);
	for (unsigned int i = 0; i < specularTextures.size(); i++)
		delete specularTextures.at(i);
	for (unsigned int i = 0; i < glowTextures.size(); i++)
		delete glowTextures.at(i);
}
void TextureManager::AddDiffuseTexture(std::string diffuseTex)
{
	ID3D11ShaderResourceView** texture = new ID3D11ShaderResourceView*;

	diffuseTex = TEXTURE_PATH + diffuseTex;
	std::wstring widestr = std::wstring(diffuseTex.begin(), diffuseTex.end());
	const wchar_t* fileName = widestr.c_str();

	hr = CreateWICTextureFromFile(gDevice, fileName, nullptr, texture);

	diffuseTextures.push_back(texture);
	diffuseTextures.shrink_to_fit();
}

void TextureManager::AddNormalTexture(std::string normalTex)
{
	ID3D11ShaderResourceView** texture = new ID3D11ShaderResourceView*;

	normalTex = TEXTURE_PATH + normalTex;
	std::wstring widestr = std::wstring(normalTex.begin(), normalTex.end());
	const wchar_t* fileName = widestr.c_str();

	hr = CreateWICTextureFromFile(gDevice, fileName, nullptr, texture);

	normalTextures.push_back(texture);
	normalTextures.shrink_to_fit();
}

void TextureManager::AddSpecularTexture(std::string specularTex)
{
	ID3D11ShaderResourceView** texture = new ID3D11ShaderResourceView*;

	specularTex = TEXTURE_PATH + specularTex;
	std::wstring widestr = std::wstring(specularTex.begin(), specularTex.end());
	const wchar_t* fileName = widestr.c_str();

	hr = CreateWICTextureFromFile(gDevice, fileName, nullptr, texture);

	specularTextures.push_back(texture);
	specularTextures.shrink_to_fit();
}

void TextureManager::AddGlowTexture(std::string glowTex)
{
	ID3D11ShaderResourceView** texture = new ID3D11ShaderResourceView*;

	glowTex = TEXTURE_PATH + glowTex;
	std::wstring widestr = std::wstring(glowTex.begin(), glowTex.end());
	const wchar_t* fileName = widestr.c_str();

	hr = CreateWICTextureFromFile(gDevice, fileName, nullptr, texture);

	glowTextures.push_back(texture);
	glowTextures.shrink_to_fit();
}

int TextureManager::GetDiffuseID(std::string diffuseTex)
{
	if (diffuseTex == "")
		return -1;
	if (this->diffuseTex.size() == 0)
	{
		this->diffuseTex.push_back(diffuseTex);
		AddDiffuseTexture(diffuseTex);
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
	this->diffuseTex.shrink_to_fit();
	AddDiffuseTexture(diffuseTex);
	return (int)(this->diffuseTex.size() - 1);
}

int TextureManager::GetNormalID(std::string normalTex)
{
	if (normalTex == "")
		return -1;
	if (this->normalTex.size() == 0)
	{
		this->normalTex.push_back(normalTex);
		AddNormalTexture(normalTex);
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
	this->normalTex.shrink_to_fit();
	AddNormalTexture(normalTex);
	return (int)(this->normalTex.size() - 1);
}

int TextureManager::GetSpecularID(std::string specularTex)
{
	if (specularTex == "")
		return -1;
	if (this->specularTex.size() == 0)
	{
		this->specularTex.push_back(specularTex);
		AddSpecularTexture(specularTex);
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
	this->specularTex.shrink_to_fit();
	AddSpecularTexture(specularTex);
	return (int)(this->specularTex.size() - 1);
}

int TextureManager::GetGlowID(std::string glowTex)
{
	if (glowTex == "")
		return -1;
	if (this->glowTex.size() == 0)
	{
		this->glowTex.push_back(glowTex);
		AddGlowTexture(glowTex);
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
	this->glowTex.shrink_to_fit();
	AddGlowTexture(glowTex);
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
	else
	{
		try
		{
			return *diffuseTextures.at(diffuseID);
		}
		catch (...)
		{
			return nullptr;
		}
	}
}

ID3D11ShaderResourceView * TextureManager::GetNormalTexture(int normalID)
{
	if (normalID == -1)
		return nullptr;
	else
	{
		try
		{
			return *normalTextures.at(normalID);
		}
		catch (...)
		{
			return nullptr;
		}
	}
}

ID3D11ShaderResourceView * TextureManager::GetSpecularTexture(int specularID)
{
	if (specularID == -1)
		return nullptr;
	else
	{
		try
		{
			return *specularTextures.at(specularID);
		}
		catch (...)
		{
			return nullptr;
		}
	}
}

ID3D11ShaderResourceView * TextureManager::GetGlowTexture(int glowID)
{
	if (glowID == -1)
		return nullptr;
	else
	{
		try
		{
			return *glowTextures.at(glowID);
		}
		catch (...)
		{
			return nullptr;
		}
	}
}
