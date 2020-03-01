#pragma once
#include "Universal.h"

struct block
{
	float xcoord;
	float ycoord;
	float xpast;
	float ypast;
	block * next;
};

class Snake
{
public:
	Snake();// float);//, int, int);
	~Snake();
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

	//int gameAreaWidth; 
	//int gameAreaHeight;
	//float step;
};

