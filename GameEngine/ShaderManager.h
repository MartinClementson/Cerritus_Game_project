#pragma once
#include "LibIncluder.h"
#include "Constants.h"




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


	//Shaders for phong shading
	ID3D11VertexShader*		PHONG_VS				= nullptr;
	ID3D11GeometryShader*	PHONG_GS				= nullptr;
	ID3D11PixelShader*		PHONG_PS				= nullptr;
	ID3D11InputLayout*		gVertexLayoutPhong		= nullptr;


	//Shaders for the Animation
	ID3D11VertexShader*		ANIMATION_VS			= nullptr;
	ID3D11GeometryShader*	ANIMATION_GS			= nullptr;
	ID3D11PixelShader*		ANIMATION_PS			= nullptr;
	ID3D11InputLayout*		gVertexLayoutAnimation  = nullptr;


public:
	ShaderManager();
	~ShaderManager();
};

