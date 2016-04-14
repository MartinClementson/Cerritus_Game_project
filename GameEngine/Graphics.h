#pragma once

#pragma region Includes
#

#include "Constants.h"
#include "LibIncluder.h"



#pragma endregion

class Graphics
{

private:
	//Device and context
	ID3D11Device* gDevice 					  = nullptr;
	ID3D11DeviceContext* gDeviceContext		  = nullptr;
	IDXGISwapChain* gSwapChain				  = nullptr;
	ID3D11RenderTargetView* gBackBufferRTV	  = nullptr;
	ID3D11Debug* debug; //Debug COM

	//Depth stencil and buffer
	ID3D11DepthStencilState* depthState		  = nullptr;
	ID3D11DepthStencilView* depthStencilView  = nullptr;
	ID3D11Texture2D* depthBuffer			  = nullptr;

	//window handle
	HWND* wndHandle							  = nullptr;

	//Buffers
	ID3D11Buffer* worldBuffer				  = nullptr; //world constBuffer
	ID3D11Buffer* camBuffer					  = nullptr; //Camera constBuffer
	ID3D11Buffer* lightBuffer				  = nullptr; //Light constBuffer
public:
	Graphics();
	~Graphics();

	void Initialize(HWND* window);
	void Release();

	HRESULT CreateDirect3DContext();

};

