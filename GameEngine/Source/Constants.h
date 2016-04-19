#pragma once
#define WIN_WIDTH 800.0
#define WIN_HEIGHT 600.0

#define WINDOWED true
#define WIREFRAME false
#define VSYNC 0 //1 == ON, 0 = OFF
#define FPS_CAP 60

#define DEBUG 2 /* 2 = debug,  or : D3D11_CREATE_DEVICE_DEBUG */

#define D3D_DEBUG_INFO


//IMPORTANT! This is only to be used with directX COM objects
#define SAFE_RELEASE(p) { if ( (p) && (p) != nullptr ) { (p)->Release(); (p) = 0; } }


#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)