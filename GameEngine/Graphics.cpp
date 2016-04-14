#include "Graphics.h"



Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

void Graphics::Initialize(HWND * window)
{


}

void Graphics::Release()
{
}

HRESULT Graphics::CreateDirect3DContext()
{


	//Swap chain description
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = WINDOW_WIDTH;
	scd.BufferDesc.Height = WINDOW_HEIGHT;
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_UNORDERED_ACCESS;
	scd.OutputWindow = *wndHandle;
	scd.SampleDesc.Count = 1;
	scd.Windowed = WINDOWED;
	scd.BufferDesc.RefreshRate.Numerator = 60; //fps cap
	scd.BufferDesc.RefreshRate.Denominator = 1;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&this->gSwapChain,
		&this->gDevice,
		NULL,
		&this->gDeviceContext);

	if (FAILED(hr))
		errorMsg("Failed to create Swap Chain");

	if (DEBUG == 2)
	{
		hr = gDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);
		if (FAILED(hr)) errorMsg("ERROR INITIALIZING DEBUG");

	}



	//Here goes depth buffer
	D3D11_TEXTURE2D_DESC desc;

	desc.Width = WINDOW_WIDTH;
	desc.Height = WINDOW_HEIGHT;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	hr = gDevice->CreateTexture2D(&desc, 0, &depthBuffer);

	hr = gDevice->CreateDepthStencilView(depthBuffer, 0, &depthStencilView);

	//Create depth state
	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //Default
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS; //Default

	gDevice->CreateDepthStencilState(&dssDesc, &depthState);




	if (SUCCEEDED(hr))
	{
		ID3D11Texture2D* pBackBuffer = nullptr;

		//D3D11_TEXTURE2D_DESC texDesc;
		//ZeroMemory(&texDesc, sizeof(texDesc));
		//texDesc.Width = WINDOW_WIDTH;
		//texDesc.Height = WINDOW_HEIGHT;
		//texDesc.MipLevels = 0;
		//texDesc.ArraySize = 1;
		//texDesc.SampleDesc.Count = 1;
		//texDesc.SampleDesc.Quality = 0;
		//texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//texDesc.Usage = D3D11_USAGE_DEFAULT;
		//texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		//texDesc.CPUAccessFlags = 0;
		//texDesc.MiscFlags = 0;

		this->gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		//hr = gDevice->CreateTexture2D(&texDesc, 0, &pBackBuffer);
		//if (FAILED(hr))
		//	errorMsg("failed to init backbuffer rtv");


		hr = this->gDevice->CreateRenderTargetView(pBackBuffer, NULL, &this->gBackbufferRTV);
		if (FAILED(hr))
			errorMsg("FAILED to create Backbuffer RTV");


		/*

		D3D11_UNORDERED_ACCESS_VIEW_DESC UAVdesc;

		ZeroMemory(&UAVdesc, sizeof(UAVdesc));
		UAVdesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		UAVdesc.Buffer.FirstElement = 0;
		UAVdesc.Format = DXGI_FORMAT_UNKNOWN;
		UAVdesc.Buffer.NumElements = WINDOW_WIDTH * WINDOW_HEIGHT;*/



		hr = this->gDevice->CreateUnorderedAccessView(pBackBuffer, nullptr, &gBackBufferUAV);
		if (FAILED(hr))
			errorMsg("Failed to create UAV");




		hr = this->gDevice->CreateShaderResourceView(pBackBuffer, nullptr, &BackBufferTexture);

		if (FAILED(hr))
			errorMsg("FAILD");



		pBackBuffer->Release();

		this->gDeviceContext->OMSetRenderTargets(1, &this->gBackbufferRTV, depthStencilView);
		currentRTV = &gBackbufferRTV;

	}

	return hr;

	return E_NOTIMPL;
}
