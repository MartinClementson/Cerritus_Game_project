#include <windows.h>
#include <sstream>

#include "./Source/Constants.h"
#include "./Source/LibIncluder.h"
#include "./Source/EngineClass/Engine.h"
#include "./Source/GameTimer/GameTimer.h"
#include "./ResourceEngine/anttweakbar/AntTweakBar.h"


HWND InitWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CalculateFPS(HWND& window, GameTimer& time);

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	#ifdef _DEBUG // this is for enabling memory leak detection
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
	
	MSG msg = { 0 };
	double tempDT = 10.0;
	// create window
	HWND wndHandle = InitWindow(hInstance);


	// window is valid
	if (wndHandle)
	{
		// display window
		ShowWindow(wndHandle, nCmdShow);
		//Create engine class
			Engine* engine = new Engine();
		engine->Initialize(&wndHandle, &hInstance);

		GameTimer* time = GameTimer::GetInstance();

		time->Reset();
		// enter message loop, loop until the message WM_QUIT is received.
		while (WM_QUIT != msg.message)
		{
			// read messages
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				// this will call the function WndProc below!
				DispatchMessage(&msg);
			}
			else
			{
				time->Tick();
				double dt = time->DeltaTime();
				CalculateFPS(wndHandle, *time);
				engine->Frame(&dt);
				
				// update/render goes here
			}
		}

		// finish the program
		engine->Release();
		delete engine;
		//delete time;
		DestroyWindow(wndHandle);
	}

	// return how the program finished.
	return (int) msg.wParam;
}

HWND InitWindow(HINSTANCE hInstance)
{
	// Every window created must belong to a CLASS, so
	// we first create a new class.
	// fill in the WNDCLASSEX structure
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;			// Which function is called for events
	wcex.hInstance      = hInstance;
	wcex.lpszClassName  = L"BasicWindow";
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
	// use the struct to register the new class.
	// the name of the class is "BasicWindow"
	if( !RegisterClassEx(&wcex) )
		return false;

	// define a struct for the window size
	RECT rc = { 0, 0, (LONG)WIN_WIDTH, (LONG)WIN_HEIGHT };
	// create the window to this size and with additional properties
	// (border, menu, etc)
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	
	HWND handle = CreateWindow(
		L"BasicWindow",			// CLASS, if does not exists fails!
		L"Cerritus",		// Window name (title)
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,		// width
		rc.bottom - rc.top,		// height
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return handle;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (TwEventWin(hWnd, message, wParam, lParam)) // send event message to AntTweakBar
		return 0; 

	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;		
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			#ifdef _DEBUG // This button function only works in debug mode. 
				PostQuitMessage(0);
			#endif
			break;
		}

	
	}

	// if we do not handle the message here, simply call the Default handler function
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CalculateFPS(HWND& window, GameTimer& time)
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;


	//Computes averages over one second period

	////
	// Time Elapsed only grows when the time between it and total time is greater than one.
	//if the time between them is greater than 1 second, we calculate the fps and time per frame
	//after that, 1.0 is added to time elapsed. Evening out the time between the two,
	//the timer does not reset, timElapsed just kinda "catches up on the total time"

	if ((time.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; //fps = frameCnt / 1
		float mspf = 1000.0f / fps; //This is the miliseconds it takes to render one frame

		std::wostringstream outs; //Format it nicely to be sent to the window
		outs.precision(6);

		outs << L"   " << L"FPS: " << fps << L"   "
			<< L"Time Per Frame: " << mspf << L" (ms)";
		SetWindowText(window, outs.str().c_str()); //update the window bar text


												   //Reset for next average
		frameCnt = 0;
		timeElapsed += 1.0f;


	}
}