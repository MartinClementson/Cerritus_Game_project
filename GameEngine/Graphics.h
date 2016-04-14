#pragma once

#pragma region Includes


#include "Constants.h"
#include "LibIncluder.h"
#include "RenderInfo.h"


#pragma endregion

class Graphics
{

private:
#pragma region DirectX Related
	//Device and context
	ID3D11Device* gDevice 					    = nullptr;
	ID3D11DeviceContext* gDeviceContext		    = nullptr;
	IDXGISwapChain* gSwapChain				    = nullptr;
	ID3D11RenderTargetView* gBackBufferRTV	    = nullptr;
	ID3D11Debug* debug; //Debug COM

	//Depth stencil and buffer
	ID3D11DepthStencilState* depthState		    = nullptr;
	ID3D11DepthStencilView* depthStencilView    = nullptr;
	ID3D11Texture2D* depthBuffer			    = nullptr;

	//window handle
	HWND* wndHandle							    = nullptr;

	//Buffers
	ID3D11Buffer* worldBuffer				    = nullptr; //world constBuffer
	ID3D11Buffer* camBuffer					    = nullptr; //Camera constBuffer
	ID3D11Buffer* lightBuffer				    = nullptr; //Light constBuffer


	//Compute shader related

	ID3D11UnorderedAccessView* gBackBufferUAV   = nullptr;
	ID3D11ShaderResourceView *BackBufferTexture = nullptr;
#pragma endregion

#pragma region Private members

	std::vector<RenderInfoObject>* gameObjects  = nullptr;

#pragma endregion


public:
	Graphics();
	~Graphics();

	void Initialize(HWND* window);
	void Release();

	void Render();

	HRESULT CreateDirect3DContext();

};

