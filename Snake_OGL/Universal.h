#pragma once
#include <windows.h>
#include <tchar.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <random>
#include <string>
#include <chrono>
#include <thread>

#define WM_END_GAME (WM_APP + 0x0001)
#define MAX_NAPTIME 150
#define MIN_NAPTIME 25
#define NAPTIME_INCREMENT 5
#define FrameTime 160.6f
#define PhysicsTime 20.0f

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

struct Globals
{
public:
	HINSTANCE hInstance;
	HWND hwnd;
	HDC   hdc;
	HGLRC hglrc;
	int width, height;
	const float step = 0.2f;
	//float frameTime = 16.6f;
};



extern Globals g;

#pragma region numbers
extern int sizes[10];
extern GLfloat DigitCol[];
extern GLfloat zero[];
extern GLfloat one[];
extern GLfloat two[];
extern GLfloat three[];
extern GLfloat four[];
extern GLfloat five[];
extern GLfloat six[];
extern GLfloat seven[];
extern GLfloat eight[];
extern GLfloat nine[];
#pragma endregion

//#include "Snake.h"
