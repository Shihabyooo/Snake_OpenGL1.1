#include "Universal.h"




int CALLBACK WinMain(HINSTANCE MainInstance, HINSTANCE PreviousMainInstance, LPSTR CMDPointer, int CMDShow)
{
	/*if (_heapchk() != _HEAPOK)
	{
		MessageBox(NULL, _T("heaperror"), _T("heaperror"), NULL);
		DebugBreak();
	}*/

#pragma region initializations
	g.hInstance = MainInstance;

	WNDCLASSEX WClass;
	MSG message;

	WClass.cbSize = sizeof(WNDCLASSEX);
	WClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WClass.lpfnWndProc = WindowProc;
	WClass.cbClsExtra = 0;
	WClass.cbWndExtra = 0;
	WClass.hInstance = g.hInstance;
	WClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WClass.lpszMenuName = NULL;
	WClass.lpszClassName = L"OGL Window Class";
	WClass.hIconSm = LoadIcon(WClass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	FTarget(); //test

	if (!RegisterClassEx(&WClass))
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
					FEndAnim();
					u = 0;
					v = 0;
					std::wstring result = L"Score =  ";
					result += std::to_wstring(Snake.SGetLength());

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
				if (u == 0.0 && v == 0.0)
				{
					if (message.wParam == VK_RETURN)
					{
						u = 0.0;
						v = step;
					}
				}
				if (message.wParam == VK_HOME)
				{
					u = 0.0;
					v = 0.0;
					Snake.SReset();
				}
				if (message.wParam == VK_UP)
				{
					if (u != 0.0)
					{
						u = 0.0;
						v = step;
					}
				}
				else if (message.wParam == VK_DOWN)
				{
					if (u != 0.0)
					{
						u = 0.0;
						v = -step;
					}
				}
				else if (message.wParam == VK_LEFT)
				{
					if (v != 0.0)
					{
						u = -step;
						v = 0.0;
					}
				}
				else if (message.wParam == VK_RIGHT)
				{
					if (v != 0.0)
					{
						u = step;
						v = 0.0;
					}
				}
				else if (message.wParam == VK_END)
				{
					Sleep(1000); //without this, clearing won't work program works faster than key presses
								//the program will move to after clearing message queue before you lift your
								//finger from the END key, do the math...
					while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) { } //clears message queue
					//test value to force pause the game
					while (1)
					{
						PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
						if (message.wParam == VK_END)
						{
							break;
						}
					}
					//end test
				}
				else if (message.wParam == VK_PRIOR)
				{
					if (naptime > 25)
					{
						naptime -= 5;
					}
				}
				else if (message.wParam == VK_NEXT)
				{
					if (naptime < 125)
					{
						naptime += 5;
					}
				}
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
			FUpdate();
		}
		else 
		{
			FUpdate();
		}
		//increments here
#pragma endregion
	}
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(g.hglrc);
	ReleaseDC(g.hwnd, g.hdc);

	return message.wParam;
}

			