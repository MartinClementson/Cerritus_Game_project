#include "ShaderManager.h"



ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext)
{
	this->gDevice			 = gDevice;
	this->gDeviceContext	 = gDeviceContext;
	CreateShaders();


	
}

void ShaderManager::Release()
{

	SAFE_RELEASE(gSampleState);


	
	SAFE_RELEASE(PHONG_VS);
	SAFE_RELEASE(PHONG_GS);
	SAFE_RELEASE(PHONG_PS);
	SAFE_RELEASE(gVertexLayoutPhong);


	//Shaders for the Animation
	SAFE_RELEASE(ANIMATION_VS);
	SAFE_RELEASE(ANIMATION_GS);
	SAFE_RELEASE(ANIMATION_PS);
	SAFE_RELEASE(gVertexLayoutAnimation);


	//Shaders for particle shading
	SAFE_RELEASE(PARTICLE_VS);
	SAFE_RELEASE(PARTICLE_GS);
	SAFE_RELEASE(PARTICLE_PS);
	SAFE_RELEASE(gVertexLayoutParticle);


	//Shaders for billboard shading
	SAFE_RELEASE(BILLBOARD_VS);
	SAFE_RELEASE(BILLBOARD_GS);
	SAFE_RELEASE(BILLBOARD_PS);
	SAFE_RELEASE(gVertexLayoutBillboard);


	//Shaders for UI 
	SAFE_RELEASE(UI_VS);
	SAFE_RELEASE(UI_GS);
	SAFE_RELEASE(UI_PS);
	SAFE_RELEASE(gVertexLayoutUI);



}

void ShaderManager::SetActiveShader(Shaders* shader)
{
	switch (*shader)
	{
	case PHONG_SHADER:
		

			this->gDeviceContext->VSSetShader(PHONG_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(PHONG_GS, nullptr, 0);
			this->gDeviceContext->PSSetShader(PHONG_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutPhong);
			
		
		break;

	case ANIMATION_SHADER:
		

			this->gDeviceContext->VSSetShader(ANIMATION_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(ANIMATION_GS, nullptr, 0);
			this->gDeviceContext->PSSetShader(ANIMATION_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutAnimation);
			
		break;

	case PARTICLE_SHADER:
		

			this->gDeviceContext->VSSetShader(PARTICLE_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(PARTICLE_GS, nullptr, 0);
			this->gDeviceContext->PSSetShader(PARTICLE_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutParticle);
			
		break;

	case BILLBOARD_SHADER:
		


			this->gDeviceContext->VSSetShader(BILLBOARD_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(BILLBOARD_GS, nullptr, 0);
			this->gDeviceContext->PSSetShader(BILLBOARD_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutBillboard);
			
		break;

	case UI_SHADER:
		

			this->gDeviceContext->VSSetShader(UI_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(UI_GS, nullptr, 0);
			this->gDeviceContext->PSSetShader(UI_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutUI);
			
		break;
	}

}




void ShaderManager::CreateShaders()
{
	if (!CreatePhongShader())
		MessageBox(NULL, L"Error compiling Phong shaders", L"Shader error", MB_ICONERROR | MB_OK);
}


#pragma region Create each individual shader

bool ShaderManager::CreatePhongShader()
{


	//Create a sample state first

	HRESULT hr;

	D3D11_SAMPLER_DESC samplerDesc;
	// use linear interpolation for minification, magnification, and mip-level sampling (quite expensive)
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	//for all filters: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476132(v=vs.85).aspx

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP; //wrap, (repeat) for use of tiling texutures
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f; //mipmap offset level
	samplerDesc.MaxAnisotropy = 1; //Clamping value used if D3D11_FILTER_ANISOTROPIC or D3D11_FILTER_COMPARISON_ANISOTROPIC is specified in Filter. Valid values are between 1 and 16.
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0; //0 most detailed mipmap level, higher number == less detail
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;


	hr = gDevice->CreateSamplerState(&samplerDesc, &gSampleState);


	if (FAILED(hr))
	{
		return false;


	}
	else
	{
		//Set sampler to pixel shader and the compute shader
		gDeviceContext->PSSetSamplers(0, 1, &this->gSampleState);
		gDeviceContext->CSSetSamplers(0, 1, &this->gSampleState);
	}

	//Load the shaders



	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"PhongShaders.hlsl",
		nullptr,
		nullptr,
		"VS_main",
		"vs_4_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &PHONG_VS);

	if (FAILED(hr))
		return false;
	//Create input layout (every vertex)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,	  0,		 0,		 D3D11_INPUT_PER_VERTEX_DATA	,0 },
	//	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	  0,		12,		 D3D11_INPUT_PER_VERTEX_DATA	,0 },
	//	{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT ,  0,		20,		D3D11_INPUT_PER_VERTEX_DATA		,0 },
	//	{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT ,  0,		32,		D3D11_INPUT_PER_VERTEX_DATA		,0 }
	};

	hr = this->gDevice->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->gVertexLayoutPhong);
	pVS->Release();
	if (FAILED(hr))
		return false;


	//Geometry shader
	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile(
		L"PhongShaders.hlsl",
		nullptr,
		nullptr,
		"GS_main",
		"gs_4_0",
		0,
		0,
		&pGS,
		nullptr);

	hr = this->gDevice->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &PHONG_GS);
	pGS->Release();

	if (FAILED(hr))
		return false;



	ID3DBlob *pPs = nullptr;
	D3DCompileFromFile(
		L"PhongShaders.hlsl",
		nullptr,
		nullptr,
		"PS_main",
		"ps_4_0",
		0,
		0,
		&pPs,
		nullptr);

	hr = this->gDevice->CreatePixelShader(pPs->GetBufferPointer(), pPs->GetBufferSize(), nullptr, &PHONG_PS);
	pPs->Release();

	if (FAILED(hr))
		return false;




	return true;
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
bool ShaderManager::CreateUiShader()
{
	return false;
}
#pragma endregion