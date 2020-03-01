#pragma once
#include <windows.h>
#include <tchar.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <random>
#include <string>
#include <chrono>

#define WM_END_GAME (WM_APP + 0x0001)
#define MAX_NAPTIME 150
#define MIN_NAPTIME 25
#define NAPTIME_INCREMENT 5

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

struct Globals
{
	HINSTANCE hInstance;
	HWND hwnd;
	HDC   hdc;
	HGLRC hglrc;
	int width, height;
	const float step = 0.2f;
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
