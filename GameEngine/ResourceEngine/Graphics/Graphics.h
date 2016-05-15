#pragma once

#pragma region Includes


#include "../../Source/Constants.h"
#include "../../Source/LibIncluder.h"
#include "../../Structs/RenderInfo.h"
#include "../ObjectNode/Render/Renderer.h"
#include "Gbuffer\Gbuffer.h"
#include "../Graphics/ShadowBuffer/ShadowBuffer.h"

#pragma endregion








#define BILLBOARDED_ARRAYS	2 //atm . projectiles and health bars
enum instancedGeometryArray
{									   
	ENEMY_1_INSTANCED,				   
	PROJECTILE_INSTANCED,										
	TRAP_BEAR_INSTANCED,										
	TRAP_FIRE_INSTANCED											
																													
};	
enum billBoardArray
{
	PROJECTILE_BILLBOARD,
	HEALTH_BAR_BILLBOARD
};

class Graphics
{									   


	struct meshIndexInArray 						  
	{												  
		 int projectileMesh			= -1;		
		 int enemy1Mesh				= -1;
		 int trapBearMesh		    = -1;
		 int trapFireMesh		    = -1;
												
		void Reset() {								  //This is used for instancing,
			this->projectileMesh	= -1;			  //when we render instanced we need to keep track of
			this->enemy1Mesh		= -1;			  // what mesh to use. Some arrays have mixed meshes
			this->trapBearMesh		= -1;			  // (for example objects array) so we can't
			this->trapFireMesh		= -1;			  // use the mesh at index 0.
		}											  //With this struct we keep track of the mesh 
		
	};										      
private:
#pragma region DirectX Related
	//Device and context
	ID3D11Device*			gDevice 							   = nullptr;
	ID3D11DeviceContext*	gDeviceContext						   = nullptr;
	IDXGISwapChain*			gSwapChain							   = nullptr;
	ID3D11RenderTargetView* gBackBufferRTV						   = nullptr;
	ID3D11Debug*			debug; //Debug COM					   
																   
	//Depth stencil and buffer									   
	ID3D11DepthStencilState* depthState							   = nullptr;
	ID3D11DepthStencilView*  depthStencilView					   = nullptr;
	ID3D11Texture2D*		 depthBuffer						   = nullptr;
																   
	//window handle												   
	HWND* wndHandle												   = nullptr;
	//Gbuffer class, for deferred shading						   
	Gbuffer* gBuffer											   = nullptr;
	ShadowBuffer* shadowBuffer									   = nullptr;
																   
	//Compute shader related									   
	ID3D11UnorderedAccessView* gBackBufferUAV					   = nullptr;
	ID3D11ShaderResourceView*  BackBufferTexture				   = nullptr;
#pragma endregion												   
																   
#pragma region Private members									   
	D3D11_VIEWPORT vp; //Viewport								   
	Renderer*	renderer										   = nullptr;
	std::vector<RenderInfoObject*>*   gameObjects				   = nullptr;
	std::vector<RenderInfoUI*    >*   uiObjects					   = nullptr;
	std::vector<RenderInfoEnemy* >*   enemyObjects				   = nullptr;
	std::vector<RenderInfoChar*  >*   charObjects				   = nullptr;
	std::vector<RenderInfoTrap*  >*   trapObjects				   = nullptr;

	InstancedData* instancedWorldDataPerFrame [INSTANCED_WORLD_BUFFER_AMOUNT] = { nullptr }; //this contains the world matrices every frame.
	unsigned int   instancesToRender		  [INSTANCED_WORLD_BUFFER_AMOUNT] = { }; //The amount of instanced geometry to render, (AFTER CULLING)

	meshIndexInArray instanceMeshIndex;

	BillboardData* billBoardArray             [BILLBOARDED_ARRAYS]	= { nullptr };
	unsigned int   billboardsToRender		  [BILLBOARDED_ARRAYS]  = { 0		};
#pragma endregion

private:
	HRESULT CreateDirect3DContext();
	void RenderScene();
	void FinishFrame();
	void SetViewPort();

	void SetShadowViewPort();
	void SetShadowMap();

	void CullGeometry();

	XMFLOAT4X4 CalculateWorldMatrix(XMFLOAT3* position, XMFLOAT3* rotation);
	XMFLOAT4X4 CalculateWorldMatrix(XMFLOAT3* position, XMFLOAT3* rotation, XMFLOAT3* scale);

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

