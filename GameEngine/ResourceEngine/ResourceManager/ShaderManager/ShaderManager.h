#pragma once
#include "../../../Source/LibIncluder.h"
#include "../../../Source/Constants.h"
#include "../../../Enumerations/Enumerations.h"




#pragma region Description

/*
This class provides a way to easily handle all the shaders used in the progam.
If there are more shaders created during the project, just add them to this class.
(But don't forget to release!)

It is pretty straight forward.
All shaders are compiled when this class is initiated using init()

To specify what shader is to be used call setActiveShaders() before the render call
The parameter is a Enum. Look at Constants.h to see all available Enums.
(Don't forget to add an enum if you add a shader to this class)


*/
#pragma endregion
class ShaderManager
{
private:
	

	// pointers to the main device and context
	ID3D11Device *gDevice							 = nullptr;
	ID3D11DeviceContext* gDeviceContext				 = nullptr;

	//SamplerStates
	ID3D11SamplerState* gSampleState				 = nullptr;


	//Shaders for phong shading
	ID3D11VertexShader*		FINAL_VS				 = nullptr;
	ID3D11PixelShader*		FINAL_PS				 = nullptr;
	ID3D11InputLayout*		gVertexLayoutFinal		 = nullptr;


	//Shaders for the Animation
	ID3D11VertexShader*		ANIMATION_VS			 = nullptr;
	ID3D11GeometryShader*	ANIMATION_GS			 = nullptr;
	ID3D11PixelShader*		ANIMATION_PS			 = nullptr;
	ID3D11InputLayout*		gVertexLayoutAnimation   = nullptr;

	//Shaders for GBuffer
	ID3D11VertexShader*		GBUFFER_VS				 = nullptr;
	ID3D11GeometryShader*	GBUFFER_GS				 = nullptr;
	ID3D11PixelShader*		GBUFFER_PS				 = nullptr;
	ID3D11InputLayout*		gVertexLayoutGBuffer	 = nullptr;

	//Shaders for ShadowShader
	ID3D11VertexShader*		SHADOW_VS				 = nullptr;
	ID3D11GeometryShader*	SHADOW_GS				 = nullptr;
	//USE GBUFFER VERTEXLAYOUT!

	//Shaders for particle shading
	ID3D11VertexShader*		PARTICLE_VS				 = nullptr;
	ID3D11GeometryShader*	PARTICLE_GS				 = nullptr;
	ID3D11PixelShader*		PARTICLE_PS				 = nullptr;
	ID3D11InputLayout*		gVertexLayoutParticle	 = nullptr;


	//Shaders for billboard shading
	ID3D11VertexShader*		BILLBOARD_VS			 = nullptr;
	ID3D11GeometryShader*	BILLBOARD_GS			 = nullptr;
	ID3D11PixelShader*		BILLBOARD_PS			 = nullptr;
	ID3D11InputLayout*		gVertexLayoutBillboard	 = nullptr;

	//Shaders for UI 
	ID3D11VertexShader*		UI_VS					= nullptr;
	ID3D11GeometryShader*	UI_GS					= nullptr;
	ID3D11PixelShader*		UI_PS					= nullptr;
	ID3D11InputLayout*		gVertexLayoutUI			= nullptr;



public:
	ShaderManager();
	~ShaderManager();

	void Initialize(ID3D11Device *gDevice, ID3D11DeviceContext* gDeviceContext);
	void Release();
	void SetActiveShader(Shaders* shader);

private:

	void CreateShaders();

	bool CreateFinalPassShaders();
	bool CreateAnimationShader();
	bool CreateGbufferShader();
	bool CreateShadowShader();
	bool CreateParticleShader();
	bool CreateBillboardShader();
	bool CreateUiShader();
};

