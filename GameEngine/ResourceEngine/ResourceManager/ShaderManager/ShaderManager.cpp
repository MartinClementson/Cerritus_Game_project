#include "ShaderManager.h"




ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

void ShaderManager::Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext)
{
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
	CreateShaders();



}

void ShaderManager::Release()
{

	SAFE_RELEASE(linearSampleState);
	SAFE_RELEASE(pointSampleState );

	
	SAFE_RELEASE(FINAL_VS);
	SAFE_RELEASE(FINAL_PS);
	SAFE_RELEASE(gVertexLayoutFinal);


	//Shaders for the Animation
	SAFE_RELEASE(ANIMATION_VS);
	SAFE_RELEASE(ANIMATION_GS);
	SAFE_RELEASE(ANIMATION_PS);
	SAFE_RELEASE(gVertexLayoutAnimation);

	//Shaders for the gbuffer
	SAFE_RELEASE(GBUFFER_VS);
	SAFE_RELEASE(GBUFFER_GS);
	SAFE_RELEASE(GBUFFER_PS);
	SAFE_RELEASE(gVertexLayoutGBuffer);

	SAFE_RELEASE(INSTANCED_GBUFFER_VS);
	SAFE_RELEASE(INSTANCED_GBUFFER_GS);
	SAFE_RELEASE(INSTANCED_GBUFFER_PS);
	SAFE_RELEASE(mInstancedGbufferLayout);


	//Shaders for shadowshader
	SAFE_RELEASE(SHADOW_VS);
	SAFE_RELEASE(SHADOW_GS);
	SAFE_RELEASE(INSTANCED_SHADOW_VS);
	SAFE_RELEASE(INSTANCED_SHADOW_GS);


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
	//SAFE_RELEASE(UI_GS);
	SAFE_RELEASE(UI_PS);
	SAFE_RELEASE(gVertexLayoutUI);


	//ComputeShaders
	SAFE_RELEASE(BLUR_CS);
	SAFE_RELEASE(BLUR_SECOND_CS);


	




}

void ShaderManager::SetActiveShader(Shaders shader)
{
	gDeviceContext->PSSetSamplers(0, 1, &this->linearSampleState);
	gDeviceContext->PSSetSamplers(1, 1, &this->pointSampleState);
	switch (shader)
	{
	case FINAL_SHADER:
		

			this->gDeviceContext->VSSetShader(FINAL_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->PSSetShader(FINAL_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutFinal);
			
		
		break;

	case ANIMATION_SHADER:
		

			this->gDeviceContext->VSSetShader(ANIMATION_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(ANIMATION_GS, nullptr, 0);
			this->gDeviceContext->PSSetShader(ANIMATION_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutAnimation);
			
		break;

	case GBUFFER_SHADER:


			this->gDeviceContext->VSSetShader(GBUFFER_VS, nullptr, 0);
			this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->GSSetShader(GBUFFER_GS, nullptr, 0);
			this->gDeviceContext->PSSetShader(GBUFFER_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutGBuffer);

		break;

	case GBUFFER_SHADER_INSTANCED:


		this->gDeviceContext->VSSetShader(INSTANCED_GBUFFER_VS, nullptr, 0);
		this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->GSSetShader(INSTANCED_GBUFFER_GS, nullptr, 0);
		this->gDeviceContext->PSSetShader(INSTANCED_GBUFFER_PS, nullptr, 0);
		this->gDeviceContext->IASetInputLayout(mInstancedGbufferLayout);

		break;

	case SHADOW_SHADER:


		this->gDeviceContext->VSSetShader(SHADOW_VS, nullptr, 0);
		this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->GSSetShader(SHADOW_GS, nullptr, 0);
		this->gDeviceContext->PSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->IASetInputLayout(gVertexLayoutGBuffer);

		break;

	case SHADOW_SHADER_INSTANCED:


		this->gDeviceContext->VSSetShader(INSTANCED_SHADOW_VS, nullptr, 0);
		this->gDeviceContext->HSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->DSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->GSSetShader(INSTANCED_SHADOW_GS, nullptr, 0);
		this->gDeviceContext->PSSetShader(nullptr, nullptr, 0);
		this->gDeviceContext->IASetInputLayout(mInstancedGbufferLayout);

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
			this->gDeviceContext->GSSetShader(nullptr, nullptr, 0);
			this->gDeviceContext->PSSetShader(UI_PS, nullptr, 0);
			this->gDeviceContext->IASetInputLayout(gVertexLayoutUI);
			
		break;

	case BLUR_SHADER:

			this->gDeviceContext->CSSetShader(BLUR_CS, nullptr, 0);

		break;

	case BLUR_SECOND_SHADER:

			this->gDeviceContext->CSSetShader(BLUR_SECOND_CS, nullptr, 0);

		break;
	}

}




void ShaderManager::CreateShaders()
{
	if (!CreateFinalPassShaders())
		MessageBox(NULL, L"Error compiling FinalPassShaders shaders", L"Shader error", MB_ICONERROR | MB_OK);
	if (!CreateGbufferShader())
		MessageBox(NULL, L"Error compiling Gbuffer shaders", L"Shader error", MB_ICONERROR | MB_OK);
	if (!CreateShadowShader())
		MessageBox(NULL, L"Error compiling Shadow shaders", L"Shader error", MB_ICONERROR | MB_OK);
	if(!CreateUiShader())
		MessageBox(NULL, L"Error compiling UI shaders", L"Shader error", MB_ICONERROR | MB_OK);
	if (!CreateInstancedGbufferShader())
		MessageBox(NULL, L"Error compiling Instanced Gbuffer shaders", L"Shader error", MB_ICONERROR | MB_OK);
	if (!CreateInstancedShadowShader())
		MessageBox(NULL, L"Error compiling instanced Shadow shaders", L"Shader error", MB_ICONERROR | MB_OK);
	if (!CreateBlurComputeShader())
		MessageBox(NULL, L"Error compiling compute shader", L"Shader error", MB_ICONERROR | MB_OK);
	if (!CreateBillboardShader())
		MessageBox(NULL, L"Error compiling instanced Shadow shaders", L"Shader error", MB_ICONERROR | MB_OK);
}


#pragma region Create each individual shader

bool ShaderManager::CreateFinalPassShaders()
{


	//Create a sample state first

	HRESULT hr;

	D3D11_SAMPLER_DESC samplerDesc;
	// use linear interpolation for minification, magnification, and mip-level sampling (quite expensive)
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;// D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	//for all filters: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476132(v=vs.85).aspx

	samplerDesc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP; //wrap, (repeat) for use of tiling texutures
	samplerDesc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias		= 0.0f; //mipmap offset level
	samplerDesc.MaxAnisotropy   = 1; //Clamping value used if D3D11_FILTER_ANISOTROPIC or D3D11_FILTER_COMPARISON_ANISOTROPIC is specified in Filter. Valid values are between 1 and 16.
	samplerDesc.ComparisonFunc  = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD			= 0; //0 most detailed mipmap level, higher number == less detail
	samplerDesc.MaxLOD			= D3D11_FLOAT32_MAX;
	samplerDesc.BorderColor[0]  = 0.0f;
	samplerDesc.BorderColor[1]  = 0.0f;
	samplerDesc.BorderColor[2]  = 0.0f;
	samplerDesc.BorderColor[3]  = 1.0f;




	hr = gDevice->CreateSamplerState(&samplerDesc, &linearSampleState);


	if (FAILED(hr))
	{
		return false;


	}
	else
	{
		//Set sampler to pixel shader and the compute shader
		gDeviceContext->PSSetSamplers(0, 1, &this->linearSampleState);
		gDeviceContext->CSSetSamplers(0, 1, &this->linearSampleState);
	}




	//Create a sample state first

	

	D3D11_SAMPLER_DESC samplerDescPoint;
	// use linear interpolation for minification, magnification, and mip-level sampling (quite expensive)
	samplerDescPoint.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
														 //for all filters: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476132(v=vs.85).aspx

	samplerDescPoint.AddressU		 = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDescPoint.AddressV		 = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDescPoint.AddressW		 = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDescPoint.MipLODBias		 = 0.0f;  //mipmap offset level
	samplerDescPoint.MaxAnisotropy	 = 1;  //Clamping value used if D3D11_FILTER_ANISOTROPIC or D3D11_FILTER_COMPARISON_ANISOTROPIC is specified in Filter. Valid values are between 1 and 16.
	samplerDescPoint.ComparisonFunc  = D3D11_COMPARISON_ALWAYS;
	samplerDescPoint.MinLOD			 = 0;			//0 most detailed mipmap level, higher number == less detail
	samplerDescPoint.MaxLOD			 = D3D11_FLOAT32_MAX;
	




	hr = gDevice->CreateSamplerState(&samplerDesc, &pointSampleState);


	if (FAILED(hr))
	{
		return false;


	}
	else
	{
		//Set sampler to pixel shader and the compute shader
		gDeviceContext->PSSetSamplers(1, 1, &this->pointSampleState);
		gDeviceContext->CSSetSamplers(1, 1, &this->pointSampleState);
	}




	//Load the shaders



	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"ResourceEngine/Shader/FinalPassShaders/FinalPassShaders.hlsl",
		nullptr,
		nullptr,
		"VS_main",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &FINAL_VS);

	if (FAILED(hr))
		return false;
	//Create input layout (every vertex)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		/*POSITION*/{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,	  0,		 0,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*UV*/		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	  0,		24,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
	};

	hr = this->gDevice->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->gVertexLayoutFinal);
	pVS->Release();
	if (FAILED(hr))
		return false;




	ID3DBlob *pPs = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/FinalPassShaders/FinalPassShaders.hlsl",
		nullptr,
		nullptr,
		"PS_main",
		"ps_5_0",
		0,
		0,
		&pPs,
		nullptr);

	hr = this->gDevice->CreatePixelShader(pPs->GetBufferPointer(), pPs->GetBufferSize(), nullptr, &FINAL_PS);
	pPs->Release();

	if (FAILED(hr))
		return false;




	return true;
}

bool ShaderManager::CreateAnimationShader()
{
	return false;
}

bool ShaderManager::CreateGbufferShader()
{

	HRESULT hr;
	//Load the shaders

	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"ResourceEngine/Shader/GBufferShader/Gbuffer.hlsl",
		nullptr,
		nullptr,
		"GBUFFER_VS_main",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &GBUFFER_VS);

	if (FAILED(hr))
		return false;
	//Create input layout (every vertex)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		/*POSITION*/	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,	  0,		 0,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*NORMAL*/		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32B32_FLOAT ,  0,		12,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*UV*/			{ "TEXCOORD",	1, DXGI_FORMAT_R32G32_FLOAT,	  0,		24,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*BITANGENT*/	{ "TEXCOORD",	2, DXGI_FORMAT_R32G32_FLOAT,	  0,		32,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*TANGENT*/		{ "TEXCOORD",	3, DXGI_FORMAT_R32G32_FLOAT,	  0,		40,		 D3D11_INPUT_PER_VERTEX_DATA		,0 }
	};

	hr = this->gDevice->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->gVertexLayoutGBuffer);
	if (FAILED(hr))
		return false;
	pVS->Release();
	

	//Geometry shader
	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/GBufferShader/Gbuffer.hlsl",
		nullptr,
		nullptr,
		"GBUFFER_GS_main",
		"gs_5_0",
		0,
		0,
		&pGS,
		nullptr);

	hr = this->gDevice->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &GBUFFER_GS);
	pGS->Release();

	if (FAILED(hr))
		return false;



	ID3DBlob *pPs = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/GBufferShader/Gbuffer.hlsl",
		nullptr,
		nullptr,
		"GBUFFER_PS_main",
		"ps_5_0",
		0,
		0,
		&pPs,
		nullptr);

	hr = this->gDevice->CreatePixelShader(pPs->GetBufferPointer(), pPs->GetBufferSize(), nullptr, &GBUFFER_PS);
	pPs->Release();

	if (FAILED(hr))
		return false;




	return true;
}

bool ShaderManager::CreateInstancedGbufferShader()
{
	HRESULT hr;
	//Load the shaders

	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"ResourceEngine/Shader/GBufferShader/GbufferShader_Instanced.hlsl",
		nullptr,
		nullptr,
		"GBUFFER_VS_main",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &INSTANCED_GBUFFER_VS);
	if (FAILED(hr))
		MessageBox(NULL, L"Error creating instanced layout", L"Shader error", MB_ICONERROR | MB_OK);



	//Create instanced vert layout
	D3D11_INPUT_ELEMENT_DESC inputDescI[] =
	{
		/*POSITION*/	{ "POSITION",	0,  DXGI_FORMAT_R32G32B32_FLOAT,	 0,		 0,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*NORMAL*/		{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32B32_FLOAT ,	 0,		12,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*UV*/			{ "TEXCOORD",	1,	DXGI_FORMAT_R32G32_FLOAT,		 0,		24,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*BITANGENT*/	{ "TEXCOORD",	2,  DXGI_FORMAT_R32G32_FLOAT,		 0,		32,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*TANGENT*/		{ "TEXCOORD",	3,  DXGI_FORMAT_R32G32_FLOAT,		 0,		40,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*WORLD MATRIX*/{ "WORLD",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	 1,		0,		 D3D11_INPUT_PER_INSTANCE_DATA		,1 },
		/*WORLD MATRIX*/{ "WORLD",		1,	DXGI_FORMAT_R32G32B32A32_FLOAT,	 1,		16,		 D3D11_INPUT_PER_INSTANCE_DATA		,1 },
		/*WORLD MATRIX*/{ "WORLD",		2,	DXGI_FORMAT_R32G32B32A32_FLOAT,	 1,		32,		 D3D11_INPUT_PER_INSTANCE_DATA		,1 },
		/*WORLD MATRIX*/{ "WORLD",		3,	DXGI_FORMAT_R32G32B32A32_FLOAT,	 1,		48,		 D3D11_INPUT_PER_INSTANCE_DATA		,1 }
	};

	hr = this->gDevice->CreateInputLayout(inputDescI, ARRAYSIZE(inputDescI), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->mInstancedGbufferLayout);
	pVS->Release();
	if (FAILED(hr))
		MessageBox(NULL, L"Error creating instanced layout", L"Shader error", MB_ICONERROR | MB_OK);




	//Geometry shader
	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/GBufferShader/GbufferShader_Instanced.hlsl",
		nullptr,
		nullptr,
		"GBUFFER_GS_main",
		"gs_5_0",
		0,
		0,
		&pGS,
		nullptr);

	hr = this->gDevice->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &INSTANCED_GBUFFER_GS);
	pGS->Release();

	if (FAILED(hr))
		return false;



	ID3DBlob *pPs = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/GBufferShader/GbufferShader_Instanced.hlsl",
		nullptr,
		nullptr,
		"GBUFFER_PS_main",
		"ps_5_0",
		0,
		0,
		&pPs,
		nullptr);

	hr = this->gDevice->CreatePixelShader(pPs->GetBufferPointer(), pPs->GetBufferSize(), nullptr, &INSTANCED_GBUFFER_PS);
	pPs->Release();

	if (FAILED(hr))
		return false;




	return true;
}

bool ShaderManager::CreateShadowShader()
{
	HRESULT hr;

	//Vertex Shader
	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"ResourceEngine/Shader/ShadowShader/ShadowShader.hlsl",
		nullptr,
		nullptr,
		"SHADOW_VS_main",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &SHADOW_VS);
	pVS->Release();
	if (FAILED(hr))
		return false;

	//Geometry shader
	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/ShadowShader/ShadowShader.hlsl",
		nullptr,
		nullptr,
		"SHADOW_GS_main",
		"gs_5_0",
		0,
		0,
		&pGS,
		nullptr);

	hr = this->gDevice->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &SHADOW_GS);
	pGS->Release();

	if (FAILED(hr))
		return false;

	return true;
}

bool ShaderManager::CreateInstancedShadowShader()
{
	HRESULT hr;

	//Vertex Shader
	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"ResourceEngine/Shader/ShadowShader/ShadowShader_Instanced.hlsl",
		nullptr,
		nullptr,
		"SHADOW_VS_main",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &INSTANCED_SHADOW_VS);

	if (FAILED(hr))
		return false;

	//Geometry shader
	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/ShadowShader/ShadowShader_Instanced.hlsl",
		nullptr,
		nullptr,
		"SHADOW_GS_main",
		"gs_5_0",
		0,
		0,
		&pGS,
		nullptr);

	hr = this->gDevice->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &INSTANCED_SHADOW_GS);
	pGS->Release();

	if (FAILED(hr))
		return false;

	return true;
}

bool ShaderManager::CreateBlurComputeShader()
{
	HRESULT hr;
	//Connecting the CS
	ID3DBlob *pCs = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/ComputeShaders/BlurCS.hlsl",
		nullptr,
		nullptr,
		"main",
		"cs_5_0",
		0,
		0,
		&pCs,
		nullptr);

	hr = gDevice->CreateComputeShader(pCs->GetBufferPointer(),
		pCs->GetBufferSize(), NULL, &BLUR_CS);

	pCs->Release();
	if (FAILED(hr))
		return false;

	ID3DBlob *pCss = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/ComputeShaders/SecondBlurCS.hlsl",
		nullptr,
		nullptr,
		"main",
		"cs_5_0",
		0,
		0,
		&pCss,
		nullptr);

	hr = gDevice->CreateComputeShader(pCss->GetBufferPointer(),
		pCss->GetBufferSize(), NULL, &BLUR_SECOND_CS);

	pCss->Release();
	if (FAILED(hr))
		return false;

	return true;
}

bool ShaderManager::CreateParticleShader()
{
	return false;
}

bool ShaderManager::CreateBillboardShader()
{

	HRESULT hr;
	//Load the shaders

	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"ResourceEngine/Shader/BillboardShader/BillboardShader.hlsl",
		nullptr,
		nullptr,
		"BILLBOARD_VS",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &BILLBOARD_VS);
	if (FAILED(hr))
		MessageBox(NULL, L"Error creating instanced layout", L"Shader error", MB_ICONERROR | MB_OK);



	//Create instanced vert layout
	D3D11_INPUT_ELEMENT_DESC inputDescI[] =
	{
		/*POSITION*/{ "POSITION",		0,  DXGI_FORMAT_R32G32B32_FLOAT,	 0,		 0,		     D3D11_INPUT_PER_VERTEX_DATA		,0 },
					{ "DIRECTION",		0,  DXGI_FORMAT_R32G32B32_FLOAT,	 0,		 12,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*SIZE*/	{ "HEIGHT"		,   0,  DXGI_FORMAT_R32_FLOAT,	         0,		 24,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
					{ "WIDTH"		,   0,  DXGI_FORMAT_R32_FLOAT,	         0,		 28,		 D3D11_INPUT_PER_VERTEX_DATA		,0 }
	};

	hr = this->gDevice->CreateInputLayout(inputDescI, ARRAYSIZE(inputDescI), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->gVertexLayoutBillboard);
	pVS->Release();
	if (FAILED(hr))
		MessageBox(NULL, L"Error creating billboard layout", L"Shader error", MB_ICONERROR | MB_OK);




	//Geometry shader
	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/BillboardShader/BillboardShader.hlsl",
		nullptr,
		nullptr,
		"BILLBOARD_GS",
		"gs_5_0",
		0,
		0,
		&pGS,
		nullptr);

	hr = this->gDevice->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &BILLBOARD_GS);
	pGS->Release();

	if (FAILED(hr))
		return false;



	ID3DBlob *pPs = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/BillboardShader/BillboardShader.hlsl",
		nullptr,
		nullptr,
		"BILLBOARD_PS",
		"ps_5_0",
		0,
		0,
		&pPs,
		nullptr);

	hr = this->gDevice->CreatePixelShader(pPs->GetBufferPointer(), pPs->GetBufferSize(), nullptr, &BILLBOARD_PS);
	pPs->Release();

	if (FAILED(hr))
		return false;




	return true;
}
bool ShaderManager::CreateUiShader()
{
	HRESULT hr;

	//Vertex Shader
	ID3DBlob* pVS = nullptr;

	D3DCompileFromFile(
		L"ResourceEngine/Shader/UIShader/UIShader.hlsl",
		nullptr,
		nullptr,
		"VS_main",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr);

	hr = this->gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &UI_VS);
	if (FAILED(hr))
		return false;

	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		/*POSITION*/{ "SV_POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,	  0,		 0,		 D3D11_INPUT_PER_VERTEX_DATA		,0 },
		/*UV*/{ "TEXCOORD",	0, DXGI_FORMAT_R32G32B32_FLOAT ,  0,		24,		 D3D11_INPUT_PER_VERTEX_DATA		,0 }
	};

	hr = this->gDevice->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->gVertexLayoutUI);
	if (FAILED(hr))
		return false;
	pVS->Release();
	//pixel shader
	ID3DBlob *pPs = nullptr;
	D3DCompileFromFile(
		L"ResourceEngine/Shader/UIShader/UIShader.hlsl",
		nullptr,
		nullptr,
		"PS_main",
		"ps_5_0",
		0,
		0,
		&pPs,
		nullptr);

	hr = this->gDevice->CreatePixelShader(pPs->GetBufferPointer(), pPs->GetBufferSize(), nullptr, &UI_PS);
	pPs->Release();

	if (FAILED(hr))
		return false;

	return true;
}
#pragma endregion