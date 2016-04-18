#include "Gbuffer.h"



Gbuffer::Gbuffer()
{
}


Gbuffer::~Gbuffer()
{
	
}

void Gbuffer::Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext)
{
	this->gDevice = gDevice;
	this->gDeviceContext = gDeviceContext;
	for (int i = 0; i < 5; i++)
	{
		HRESULT hr;

		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;


		ZeroMemory(&textureDesc, sizeof(textureDesc));
		//Set up the render texture desciption

		textureDesc.Width = WIN_WIDTH;
		textureDesc.Height = WIN_HEIGHT;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		//Create the render target Texture

		hr = gDevice->CreateTexture2D(&textureDesc, NULL, &gBufferTextures[i]);
		if (FAILED(hr))
			return false;



		//set up description for render target view
		renderTargetDesc.Format = textureDesc.Format;
		renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetDesc.Texture2D.MipSlice = 0;

		//Create render target

		hr = gDevice->CreateRenderTargetView(renderTargetTexture, &renderTargetDesc, &renderTargetView);
		if (FAILED(hr))
			return false;

		//Set up the shader resource view

		resourceViewDesc.Format = textureDesc.Format;
		resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		resourceViewDesc.Texture2D.MostDetailedMip = 0;
		resourceViewDesc.Texture2D.MipLevels = 1;

		//Create the resourceView;

		hr = device->CreateShaderResourceView(renderTargetTexture, &resourceViewDesc, &shaderResourceView);
		if (FAILED(hr))
			return false;
		return true;


	}


}

void Gbuffer::Release()
{
	for (int i = 0; i < 5; i++)
	{
		SAFE_RELEASE(textureRTVs[i]);

		SAFE_RELEASE(shaderResourceViews[i]);

		SAFE_RELEASE(gBufferTextures[i]);
	}

}

void Gbuffer::SetToRender()
{
}

void Gbuffer::SetToRead()
{
}
