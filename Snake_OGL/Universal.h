#pragma once
#include <windows.h>
#include <tchar.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <random>
#include <string>

#define WM_END_GAME (WM_APP + 0x0001)

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

struct Globals
{
	HINSTANCE hInstance;
	HWND hwnd;
	HDC   hdc;
	HGLRC hglrc;
	int width, height;
};

struct block
{
	float xcoord;
	float ycoord;
	float xpast;
	float ypast;
	block * next;
};

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

extern Globals g;
extern float u;
extern float v;
extern const float step;
extern bool growth_flag;
extern int growth_count;
extern int naptime;
//extern float xta;
//extern float yta;



LRESULT CALLBACK WindowProc(HWND DPHandle, UINT Message, WPARAM MessageParam1, LPARAM MessageParam2);
void FDraw();
void FHead(float, float);
void FBlock(float, float);
void sleep();
void FUpdate();
void FTarget();
void FEndAnim();
void FDrawScore();
void FScore();


class snake
{
public:
	snake();
	bool SAddBlock();
	bool SUpdateHead(float, float);
	bool SUpdateTail(int);
	block SGetBlock(int); //input is order of block
	int SGetLength();
	bool SCheckIntersection(float, float); //to be called in FTarget to check that spawn point isn't filled by snake
	bool SCheckSelfCollision(); //called to check for self collision
	bool SCheckWallCollision(); //called to check for collision with wall
	bool SReset(); 

private:
	block * start;
	int length;
};


extern snake Snake;