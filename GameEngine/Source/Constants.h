#pragma once
#define WIN_WIDTH 800.0
#define WIN_HEIGHT 600.0

#define SHADOW_WIDTH 2048.0
#define SHADOW_HEIGHT 2048.0

//////////////////////////////////////////
//DIS IS BECAUSE JOHAN ASKED ME TO CHANGE AMOUNT OF TEXTURES TO MUCH
#define TEXTUREAMOUNT 6
#define SHADOWMAPAMOUNT 1
#define LIGHT_SHADOW_AMOUNT 4

#define MAX_NUM_POINTLIGHTS 20
#define MAX_NUM_DIRLIGHTS	20
#define MAX_NUM_SPOTLIGHTS	20
////////////////////////////////////

#define WINDOWED true
#define WIREFRAME false
#define VSYNC 1 //1 == ON, 0 = OFF
#define FPS_CAP 60

#define DEBUG 0 /* 2 = debug,  or : D3D11_CREATE_DEVICE_DEBUG */

#define D3D_DEBUG_INFO
#define TEXTURE_PATH "textures/"
#define MODEL_PATH "models/"

//IMPORTANT! This is only to be used with directX COM objects
#define SAFE_RELEASE(p) { if ( (p) && (p) != nullptr ) { (p)->Release(); (p) = 0; } }


#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)


#define CAMERABUFFER_INDEX 0
#define WORLDBUFFER_INDEX 1
#define LIGHTBUFFER_INDEX 2
#define SAMPLEBOOLSBUFFER_INDEX 3