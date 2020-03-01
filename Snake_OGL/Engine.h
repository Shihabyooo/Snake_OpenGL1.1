#pragma once
#include "Universal.h"
#include "Snake.h"
#include "GameTime.h"

class Engine
{
public:

	Engine();
	~Engine();

	void UpdateGame();
	
	void ResetGame();

	void SetDirection(int, int);
	void IncrementSpeed(int);

	void Target(); //2020 genuinely don't remember what this method does.
	int GetScore();
	void StartGame();

private:
	void DrawFrame();

	void UpdateBlock(float, float);
	void UpdateHead(float, float);
	void UpdateScore();
	void DrawScore(GLfloat * digit, int digitverts, int digitorder);
	bool CheckCollision();
	void EndAnimation();
	int IRandom(int, int);

	float u;
	float v;
	float xta = 0.0f;
	float yta = 0.0f;
	//const float step = 0.2f;
	//float scstep = g.step * 2; //to control score size
	float scstep = 0.6; //to control score size
	bool growth_flag;
	int growth_count;
	//int naptime = 50;
	float gameSpeed = 16.7f; //2020 Because I was an noob when I made the game, I didn't put into account that physics and game calculations should be decoupled from frame update rate, so now I'm stuck with one speed for both
	bool isGameRunning = false;

	GameTime * time;
	Snake * snake;
};