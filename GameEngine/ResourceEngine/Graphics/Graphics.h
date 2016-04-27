#pragma once

#pragma region Includes


#include "../../Source/Constants.h"
#include "../../Source/LibIncluder.h"
#include "../../Structs/RenderInfo.h"
#include "../ObjectNode/Render/Renderer.h"
#include "Gbuffer\Gbuffer.h"

#pragma endregion

class Graphics
{

private:
#pragma region DirectX Related
	//Device and context
	ID3D11Device*			gDevice 				 = nullptr;
	ID3D11DeviceContext*	gDeviceContext			 = nullptr;
	IDXGISwapChain*			gSwapChain				 = nullptr;
	ID3D11RenderTargetView* gBackBufferRTV			 = nullptr;
	ID3D11Debug*			debug; //Debug COM

	//Depth stencil and buffer
	ID3D11DepthStencilState* depthState				 = nullptr;
	ID3D11DepthStencilView*  depthStencilView		 = nullptr;
	ID3D11Texture2D*		 depthBuffer			 = nullptr;

	//window handle
	HWND* wndHandle									 = nullptr;
	//Gbuffer class, for deferred shading
	Gbuffer* gBuffer								 = nullptr;


	//Compute shader related
	ID3D11UnorderedAccessView* gBackBufferUAV		 = nullptr;
	ID3D11ShaderResourceView*  BackBufferTexture	 = nullptr;
#pragma endregion

#pragma region Private members
	D3D11_VIEWPORT vp; //Viewport
	Renderer*	renderer	
		= nullptr;
	std::vector<RenderInfoObject*>* gameObjects		 = nullptr;
	std::vector<RenderInfoUI*>*     uiObjects		 = nullptr;
	std::vector<RenderInfoEnemy*>*  enemyObjects	 = nullptr;
	std::vector<RenderInfoChar*>*   charObjects		 = nullptr;
	std::vector<RenderInfoTrap*>*   trapObjects		 = nullptr;
	
#pragma endregion

private:
	HRESULT CreateDirect3DContext();
	void RenderScene();
	void FinishFrame();
	void SetViewPort();

	void SetShadowViewPort();
	void SetShadowMap();

	Graphics();
public:
	~Graphics();

	void Initialize(HWND* window);
	void Release();

	void Render();
	void QueueRender(RenderInfoObject *object);

	
	void QueueRender(RenderInfoUI* object);
	void QueueRender(RenderInfoEnemy* object);
	void QueueRender(RenderInfoChar* object);
	void QueueRender(RenderInfoTrap* object);
	XMFLOAT4 mouseWorldPos;
	

	//Singleton for the graphics class 
	static Graphics* GetInstance();

	XMFLOAT3 GetPlayerDirection(XMFLOAT2 mousePos,  XMFLOAT3 playerPos);

};

