#include "ShadowBuffer.h"

ShadowBuffer::ShadowBuffer()
{
}

ShadowBuffer::~ShadowBuffer()
{
}

void ShadowBuffer::Initialize(ID3D11Device * gDevice, ID3D11DeviceContext * gDeviceContext)
{
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;

	#pragma region create shadowmap stuff
	HRESULT hr;

	D3D11_TEXTURE2D_DESC ShadowTexDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewShadowDesc;

	ZeroMemory(&ShadowTexDesc, sizeof(ShadowTexDesc));

	//Set up the render texture desciption

	ShadowTexDesc.Width = (UINT)SHADOW_WIDTH;
	ShadowTexDesc.Height = (UINT)SHADOW_HEIGHT;
	ShadowTexDesc.MipLevels = 1;
	ShadowTexDesc.ArraySize = LIGHTAMOUNT;
	ShadowTexDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	ShadowTexDesc.SampleDesc.Count = 1;
	ShadowTexDesc.Usage = D3D11_USAGE_DEFAULT;
	ShadowTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	ShadowTexDesc.CPUAccessFlags = 0;
	ShadowTexDesc.MiscFlags = 0;

	//Create the render target Texture

	hr = gDevice->CreateTexture2D(&ShadowTexDesc, NULL, &shadowMapTexure);
	if (FAILED(hr))
		MessageBox(NULL, L"Failed to create  Gbuffer ShadowMap", L"Error", MB_ICONERROR | MB_OK);

	//create depth stencil

	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
	descDSV.Texture2DArray.ArraySize = LIGHTAMOUNT;
	descDSV.Texture2DArray.FirstArraySlice = 0;
	descDSV.Texture2DArray.MipSlice = 0;

	hr = gDevice->CreateDepthStencilView(shadowMapTexure, &descDSV, &shadowMapStencilView);
	if (FAILED(hr))
		MessageBox(NULL, L"Failed to create  Gbuffer ShadowMap DepthStencils", L"Error", MB_ICONERROR | MB_OK);


	//Set up the shader resource view

	resourceViewShadowDesc.Format = DXGI_FORMAT_R32_FLOAT;
	resourceViewShadowDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	resourceViewShadowDesc.Texture2DArray.ArraySize = LIGHTAMOUNT;
	resourceViewShadowDesc.Texture2DArray.FirstArraySlice = 0;
	resourceViewShadowDesc.Texture2DArray.MostDetailedMip = 0;
	resourceViewShadowDesc.Texture2DArray.MipLevels = 1;

	//Create the resourceView;

	hr = gDevice->CreateShaderResourceView(shadowMapTexure, &resourceViewShadowDesc, &shadowShaderResourceView);
	if (FAILED(hr))
		MessageBox(NULL, L"Failed to create  Gbuffer ShadowMap resource", L"Error", MB_ICONERROR | MB_OK);
#pragma endregion
}

void ShadowBuffer::Release()
{
		SAFE_RELEASE(shadowMapStencilView);
		SAFE_RELEASE(shadowShaderResourceView);
		SAFE_RELEASE(shadowMapTexure);
}

void ShadowBuffer::ShadowSetToRender()
{
	gDeviceContext->OMSetRenderTargets(0, NULL, shadowMapStencilView);
}
void ShadowBuffer::ShadowSetToRead()
{
	this->gDeviceContext->PSSetShaderResources(4, SHADOWMAPAMOUNT, &this->shadowShaderResourceView);
}

void ShadowBuffer::ClearShadowGbuffer()
{
	this->gDeviceContext->ClearDepthStencilView(this->shadowMapStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

