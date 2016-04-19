#include "Graphics.h"



Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	if (gameObjects != nullptr)
		delete gameObjects;
	if (renderer != nullptr)
		delete renderer;
}

void Graphics::Initialize(HWND * window)
{
	HRESULT hr;
	this->wndHandle = window;

	hr = CreateDirect3DContext();

	gameObjects = new std::vector<RenderInfoObject*>;
	renderer = new Renderer();
	renderer->Initialize(gDevice,this->gDeviceContext);
}

void Graphics::Release()
{

#pragma region Release custom classes

	renderer->Release();
#pragma endregion




	

	SAFE_RELEASE(depthState);
	SAFE_RELEASE(depthStencilView);
	SAFE_RELEASE(depthBuffer);


	SAFE_RELEASE(gBackBufferUAV);
	SAFE_RELEASE(BackBufferTexture);


	SAFE_RELEASE(gBackBufferRTV);
	SAFE_RELEASE(gSwapChain);
	SAFE_RELEASE(gDeviceContext);
	SAFE_RELEASE(gDevice);
	if (DEBUG == 2)
	{
	
		debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		SAFE_RELEASE(debug);
	}
}

void Graphics::Render() //manage RenderPasses here
{
	SetViewPort();

	//MOVE THIS DOWN ONCE IT WORKS
	float clearColor[] = { 0, 0, 1, 1 };
	this->gDeviceContext->OMSetRenderTargets(1, &this->gBackBufferRTV, depthStencilView);
	this->gDeviceContext->ClearDepthStencilView(this->depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	this->gDeviceContext->ClearRenderTargetView(gBackBufferRTV, clearColor);
	
	RenderScene();

	FinishFrame();


}

void Graphics::RenderScene()
{
	this->renderer->RenderPlaceHolder();
	for (unsigned int i = 0; i < gameObjects->size(); i++)
	{
		//renderer->Render(gameObjects->at(i));

	}

}

void Graphics::FinishFrame() // this one clears the graphics for this frame. So that it can start a new cycle next frame
{
	gameObjects->clear(); //clear the queue

	this->gSwapChain->Present(VSYNC, 0); //Change front and back buffer after rendering
	gDeviceContext->ClearState();
}

void Graphics::SetViewPort()
{
	vp.Width = (float)WIN_WIDTH;
	vp.Height = (float)WIN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	this->gDeviceContext->RSSetViewports(1, &vp);

}


HRESULT Graphics::CreateDirect3DContext()
{


	//Swap chain description
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = (UINT)WIN_WIDTH;
	scd.BufferDesc.Height = (UINT)WIN_HEIGHT;
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_UNORDERED_ACCESS;
	scd.OutputWindow = *wndHandle;
	scd.SampleDesc.Count = 1;
	scd.Windowed = WINDOWED;
	scd.BufferDesc.RefreshRate.Numerator = FPS_CAP; //fps cap
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
	{

		MessageBox(*wndHandle, L"Failed to create Swap Chain", L"Error", MB_ICONERROR | MB_OK);
		return hr;
	}



	if (DEBUG == 2)
	{
		hr = gDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);
		if (FAILED(hr))MessageBox(*wndHandle, L"ERROR INITIALIZING DEBUG", L"Error", MB_ICONERROR | MB_OK); 

	}



	//Here goes depth buffer
	D3D11_TEXTURE2D_DESC desc;

	desc.Width = (UINT)WIN_WIDTH;
	desc.Height = (UINT)WIN_HEIGHT;
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

	


		hr = this->gDevice->CreateRenderTargetView(pBackBuffer, NULL, &this->gBackBufferRTV);
		if (FAILED(hr))
		{

			MessageBox(*wndHandle, L"FAILED to create Backbuffer RTV", L"Error", MB_ICONERROR | MB_OK);
			return hr;
		}
		


		/*

		D3D11_UNORDERED_ACCESS_VIEW_DESC UAVdesc; //return to this when implementing compute shaders

		ZeroMemory(&UAVdesc, sizeof(UAVdesc));
		UAVdesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		UAVdesc.Buffer.FirstElement = 0;
		UAVdesc.Format = DXGI_FORMAT_UNKNOWN;
		UAVdesc.Buffer.NumElements = WINDOW_WIDTH * WINDOW_HEIGHT;*/



		hr = this->gDevice->CreateUnorderedAccessView(pBackBuffer, nullptr, &gBackBufferUAV);

		if (FAILED(hr))
		{

			MessageBox(*wndHandle, L"Failed to create UAV", L"Error", MB_ICONERROR | MB_OK);
			return hr;
		}




		hr = this->gDevice->CreateShaderResourceView(pBackBuffer, nullptr, &BackBufferTexture);

		if (FAILED(hr))
		{

			MessageBox(*wndHandle, L"FAILED to create Backbuffer SRV", L"Error", MB_ICONERROR | MB_OK);
			return hr;
		}


		pBackBuffer->Release();

		this->gDeviceContext->OMSetRenderTargets(1, &this->gBackBufferRTV, depthStencilView);

	}

	return hr;

}




#pragma region QueueRender functions

void Graphics::QueueRender(RenderInfoObject *object)
{
	this->gameObjects->push_back(object);
}

void Graphics::QueueRender(RenderInfoUI * object)
{
}

void Graphics::QueueRender(RenderInfoEnemy * object)
{
}

void Graphics::QueueRender(RenderInfoChar * object)
{
}

void Graphics::QueueRender(RenderInfoTrap * object)
{
	//this->trapObjects->push_back(object);
}

Graphics * Graphics::GetInstance()
{
	static Graphics instance;
	return &instance;
}

#pragma endregion