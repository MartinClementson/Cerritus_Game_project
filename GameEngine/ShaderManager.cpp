#include "ShaderManager.h"



ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext)
{

}

void ShaderManager::Release()
{
}




void ShaderManager::CreateShaders()
{

}


#pragma region Create each individual shader

bool ShaderManager::CreatePhongShader()
{
	return false;
}

bool ShaderManager::CreateAnimationShader()
{
	return false;
}

bool ShaderManager::CreateParticleShader()
{
	return false;
}

bool ShaderManager::CreateBillboardShader()
{
	return false;
}
#pragma endregion