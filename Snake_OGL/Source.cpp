#include "Universal.h"
#include "Engine.h"

Engine gameEngine;
Globals g;

LRESULT CALLBACK WindowProc(HWND DPHandle, UINT Message, WPARAM MessageParam1, LPARAM MessageParam2)
{
	static RECT rect2 = { 0,0,100,100 };

	switch (Message)
	{
	case WM_CREATE:
		//Beep(50, 10);
		return 0;
		break;
		//copied from example

	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(DPHandle, &ps);
		//SetTextColor(hdc, 0x00000000);
		//SetBkMode(hdc, TRANSPARENT);
		//DrawText(hdc, _T("test"), -1, &rect2, DT_SINGLELINE | DT_NOCLIP);
		EndPaint(DPHandle, &ps);
		return 0;
		break;
		//copied from example.
	case WM_KEYDOWN:
		switch (MessageParam1)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(1337);
		break;
	default:
		return DefWindowProc(DPHandle, Message, MessageParam1, MessageParam2);
		break;
	}

	return DefWindowProc(DPHandle, Message, MessageParam1, MessageParam2);
}


int CALLBACK WinMain(HINSTANCE MainInstance, HINSTANCE PreviousMainInstance, LPSTR CMDPointer, int CMDShow)
{
	if (_heapchk() != _HEAPOK) //2020 Can't remember where I got this from, nor why... :|
	{
		MessageBox(NULL, _T("heaperror"), _T("heaperror"), NULL);
		DebugBreak();
	}

#pragma region initializations
	g.hInstance = MainInstance;

	WNDCLASSEX wlass;
	MSG message;

	wlass.cbSize = sizeof(WNDCLASSEX);
	wlass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wlass.lpfnWndProc = WindowProc;
	wlass.cbClsExtra = 0;
	wlass.cbWndExtra = 0;
	wlass.hInstance = g.hInstance;
	wlass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wlass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wlass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wlass.lpszMenuName = NULL;
	wlass.lpszClassName = L"OGL Window Class";
	wlass.hIconSm = LoadIcon(wlass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	gameEngine.Target(); //test

	if (!RegisterClassEx(&wlass))
	{
		MessageBox(NULL, _T("Class registration error!"), _T("Could not register window class!"), NULL);
		return 1;
	}
	
	RECT WindowRect = {50,50,550,550};

	g.width = WindowRect.right - WindowRect.left;
	g.height = WindowRect.bottom - WindowRect.top;
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, false);

	g.hwnd = CreateWindow(L"OGL Window Class", _T("Snake (Deprecated-OpenGL)"),
		WS_OVERLAPPEDWINDOW,
		WindowRect.left, WindowRect.top,
		WindowRect.right - WindowRect.left, 50+WindowRect.bottom - WindowRect.top,
		NULL, NULL, g.hInstance, NULL);

	if (!g.hwnd)
	{
		MessageBox(NULL, _T("Window Creation Error"), _T("Could not create window!"), NULL);
		return 1;
	}
	ShowWindow(g.hwnd, CMDShow);

	g.hdc = GetDC(g.hwnd);

	PIXELFORMATDESCRIPTOR PFD = { 0 };
	PFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	PFD.nVersion = 1;
	PFD.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	PFD.iPixelType = PFD_TYPE_RGBA;
	PFD.cColorBits = 24;
	PFD.cDepthBits = 32;

	int ChosenPF = ChoosePixelFormat(g.hdc, &PFD);

	if (ChosenPF == 0)
	{
		MessageBox(NULL, _T("Pixel Format Choice Error"), _T("No Pixel Format was chosen"), NULL);
		return 1;
	}

	int result = SetPixelFormat(g.hdc, ChosenPF, &PFD);

	if (result == NULL)
	{
		FatalAppExit(NULL, TEXT("SetPixelFormat() failed!"));
	}

	g.hglrc = wglCreateContext(g.hdc);
	wglMakeCurrent(g.hdc, g.hglrc);
#pragma endregion

	while (1)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_USER)
			{
				if (message.wParam == WM_END_GAME)
				{
					//FEndAnim();
					//u = 0;
					//v = 0;
					gameEngine.SetDirection(0, 0);
					std::wstring result = L"Score =  ";
					result += std::to_wstring(gameEngine.GetScore());

					MessageBox(NULL, result.data(), _T("Game Over!"), NULL);
					while (message.message != WM_QUIT && message.wParam != VK_HOME)
					{
						PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
						TranslateMessage(&message);
						DispatchMessage(&message);
					}
					
				}
			}
			if (message.message == WM_QUIT)
			{
				break;
			}
#pragma region controls
			if (message.message == WM_KEYDOWN)
			{
				
				if (message.wParam == VK_RETURN)
				{
					gameEngine.StartGame();
				}
				if (message.wParam == VK_HOME)
				{
					gameEngine.ResetGame();
				}
				if (message.wParam == VK_UP)
				{
					gameEngine.SetDirection(1, 0);
				}
				else if (message.wParam == VK_DOWN)
				{
					gameEngine.SetDirection(-1, 0);
				}
				else if (message.wParam == VK_LEFT)
				{
					gameEngine.SetDirection(0, -1);
				}
				else if (message.wParam == VK_RIGHT)
				{
					gameEngine.SetDirection(0, 1);
				}
				else if (message.wParam == VK_END)
				{
					//Sleep(1000); //without this, clearing won't work program works faster than key presses
					//			//the program will move to after clearing message queue before you lift your
					//			//finger from the END key, do the math...
					//while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) { } //clears message queue
					////test value to force pause the game
					//while (1)
					//{
					//	PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
					//	if (message.wParam == VK_END)
					//	{
					//		break;
					//	}
					//}
					////end test
				}
				else if (message.wParam == VK_PRIOR)
				{
					gameEngine.IncrementSpeed(-1);
				}
				else if (message.wParam == VK_NEXT)
				{
					gameEngine.IncrementSpeed(1);
				}
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//increments here
#pragma endregion
		gameEngine.UpdateGame();

	}
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(g.hglrc);
	ReleaseDC(g.hwnd, g.hdc);

	return message.wParam;
}

			