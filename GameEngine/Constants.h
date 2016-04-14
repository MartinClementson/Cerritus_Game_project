#pragma once
#define WIN_WIDTH 800.0f
#define WIN_HEIGHT 600.0f

#define WINDOWED true
#define WIREFRAME false
#define VSYNC 1 //1 == ON, 0 = OFF
#define FPS_CAP 60

#define DEBUG 2 /* 2 = debug,  or : D3D11_CREATE_DEVICE_DEBUG */
#define DIRECTINPUT_VERSION 0x0800
#define D3D_DEBUG_INFO

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }
