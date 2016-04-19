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


	HRESULT hr;

	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;


	ZeroMemory(&textureDesc, sizeof(textureDesc));
	//Set up the render texture desciption

	textureDesc.Width = (UINT)WIN_WIDTH;
	textureDesc.Height = (UINT)WIN_HEIGHT;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	textureDesc.ArraySize = TEXTUREAMOUNT; //assigning how big the array will be


										   //set up description for render target view
	renderTargetDesc.Format = textureDesc.Format;
	renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetDesc.Texture2D.MipSlice = 0;


	//Set up the shader resource view

	resourceViewDesc.Format = textureDesc.Format;
	resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	resourceViewDesc.Texture2DArray.ArraySize = TEXTUREAMOUNT;
	resourceViewDesc.Texture2DArray.FirstArraySlice = 0;
	resourceViewDesc.Texture2DArray.MipLevels = 1;
	resourceViewDesc.Texture2DArray.MostDetailedMip = 0;



	for (int i = 0; i < TEXTUREAMOUNT; i++)
	{
	
		//Create the render target Texture

		hr = gDevice->CreateTexture2D(&textureDesc, NULL, &gBufferTextures[i]);
		if (FAILED(hr))
			MessageBox(NULL, L"Failed to create  Gbuffer", L"Error", MB_ICONERROR | MB_OK);

		//Create render target

		hr = gDevice->CreateRenderTargetView(gBufferTextures[i], &renderTargetDesc, &textureRTVs[i]);
		if (FAILED(hr))
			MessageBox(NULL, L"Failed to create  Gbuffer", L"Error", MB_ICONERROR | MB_OK);

		//Create the resourceView;



	}

	//This creates an array of All the textures, that's why we only do this once!
		hr = gDevice->CreateShaderResourceView(*gBufferTextures, &resourceViewDesc, shaderResourceViews);
		if (FAILED(hr))
			MessageBox(NULL, L"Failed to create  Gbuffer", L"Error", MB_ICONERROR | MB_OK);



	for (int i = 0; i < TEXTUREAMOUNT; i++)
	{

		SAFE_RELEASE(gBufferTextures[i]);
	}




}

void Gbuffer::Release()
{
	for (int i = 0; i < TEXTUREAMOUNT; i++)
	{
		SAFE_RELEASE(textureRTVs[i]);

		SAFE_RELEASE(shaderResourceViews[i]);

		SAFE_RELEASE(gBufferTextures[i]);
	}

}

void Gbuffer::SetToRender(ID3D11DepthStencilView* depthStencilView) ///Set the textures as RTVs so that we can render to them
{

	//Take the textures of as ResourceViews and set them as render targets
	ID3D11ShaderResourceView * tab[TEXTUREAMOUNT];
	for (int i = 0; i < TEXTUREAMOUNT; i++)
		tab[i] = NULL;

	this->gDeviceContext->PSSetShaderResources(0, TEXTUREAMOUNT, tab); //kan vara fel, debugga senare


	gDeviceContext->OMSetRenderTargets(TEXTUREAMOUNT, this->textureRTVs, depthStencilView);


}

void Gbuffer::SetToRead(ID3D11RenderTargetView* newTarget)
{
	this->gDeviceContext->OMSetRenderTargets(1, &newTarget,  NULL);
	this->gDeviceContext->PSSetShaderResources(0, TEXTUREAMOUNT, this->shaderResourceViews);


}
void Gbuffer::ClearGbuffer()
{


	float color[4];
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;

	//Clear backbuffers
	for (int i = 0; i < TEXTUREAMOUNT; i ++)
		this->gDeviceContext->ClearRenderTargetView(this->textureRTVs[i], color);

	//clearDepthBuffer
	//deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//Might not be needed when only using one camera, 
	return;
	
}