#pragma once
#include "Universal.h"
#include "Snake.h"
//LRESULT CALLBACK WindowProc(HWND DPHandle, UINT Message, WPARAM MessageParam1, LPARAM MessageParam2);
//void FDraw(); //
//void FHead(float, float); //
//void FBlock(float, float); //
//void sleep();
//void FUpdate(); //
//void FTarget(); //
//void FEndAnim(); //
//void FDrawScore(); 
//void FScore(); //
//void ResetGame(); //


class Engine
{
public:

	Engine();
	~Engine();

	void DrawFrame();
	void UpdateGame();
	void ResetGame();

	void SetDirection(int, int);
	void IncrementSpeed(int);

	void Target(); //2020 genuinely don't remember what this method does.
	int GetScore();
	void StartGame();

private:
	void UpdateBlock(float, float);
	void UpdateHead(float, float);
	void UpdateScore();
	void DrawScore(GLfloat * digit, int digitverts, int digitorder);
	bool CheckCollision();
	void EndAnimation();
	void sleep(); //TODO 2020 remove this after implementing chrono timer
	int IRandom(int, int);

	float u;
	float v;
	float xta = 0.0f;
	float yta = 0.0f;
	//const float step = 0.2f;
	float scstep = g.step * 2; //to control score size
	bool growth_flag;
	int growth_count;
	int naptime = 50;
	bool isGameRunning = false;

	Snake * snake;
};