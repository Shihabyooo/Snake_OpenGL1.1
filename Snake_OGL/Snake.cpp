#include "Snake.h"


Snake::Snake() //float _step)// , int _width, int _height)
{
	start = new block;
	start->xcoord = 0;
	start->ycoord = 0;
	start->xpast = 0;
	start->ypast = 0;
	start->next = NULL;
	length = 0;


}

Snake::~Snake()
{
}

bool Snake::SUpdateHead(float x, float y)
{

	start->xpast = start->xcoord;
	start->ypast = start->ycoord;
	start->xcoord = x;
	start->ycoord = y;
	return true;

}

bool Snake::SUpdateTail(int order)
{
	//TODO 2020 consider not updating the entire tail, rather only the end block, since it's the only one that -visually- change place.
	//TODO add safeguard against passing something less than 1 or greater than length to this method
	block * traverser = start;
	block * traverser2;
	int counter = 1;

	while (counter <= length)
	{
		traverser2 = traverser->next;
		if (counter == order)
		{
			traverser2->xpast = traverser2->xcoord;
			traverser2->ypast = traverser2->ycoord;
			traverser2->xcoord = traverser->xpast;
			traverser2->ycoord = traverser->ypast;
			return true;
		}
		traverser = traverser2;
		counter++;
	}
	return false;
}

block Snake::SGetBlock(int order)
{
	block result;
	block * traverser = start;
	int counter = 0;

	while (counter <= length)
	{
		if (counter == order)
		{
			result.xcoord = traverser->xcoord;
			result.ycoord = traverser->ycoord;
			result.xpast = traverser->xpast;
			result.ypast = traverser->ypast;
			result.next = traverser->next;
			break;
		}
		traverser = traverser->next;
		counter++;
	}
	return result;
}

bool Snake::SAddBlock()
{
	block * existingblock = start;
	block * newblock;
	int counter = 0;

	while (1)
	{
		if (counter > length)
		{
			MessageBox(0, _T("Error at Snake.SAddBlock"), _T("Error"), 0);
		}

		if (existingblock->next == NULL)
		{
			newblock = new block;
			newblock->xcoord = existingblock->xpast;
			newblock->ycoord = existingblock->ypast;
			newblock->xpast = newblock->xcoord;
			newblock->ypast = newblock->ycoord;
			newblock->next = NULL;
			existingblock->next = newblock;
			length++;
			return true;
		}
		existingblock = existingblock->next;

		counter++;
	}
	return false;
}

int Snake::SGetLength()
{
	return length;
}

bool Snake::SCheckIntersection(float x, float y)
{
	if (length < 2) //without this (or another check somewhere else) the program will infinite loop 
					//I have a vague idea why, but not an exact one, yet! :|
	{
		return false;
	}
	for (int i = 0; i <= length; i++)
	{
		//if (abs(Snake.SGetBlock(i).xcoord - x) < 0.1*step && abs(Snake.SGetBlock(i).ycoord - y) < 0.1*step) 
		if (abs(SGetBlock(i).xcoord - x) < 0.1*g.step && abs(SGetBlock(i).ycoord - y) < 0.1*g.step)
			//TODO there is a potential error here (And in FTCollision) in case ycoord and y exist with different signs.
			//because of float accuracy. e.g, at ~0.0 cord, y gets -0.00001, and ycoord 0.00001.
			//only way to solve that is abs() each one, then abs() the difference. 
			//eg: abs(abs(ycoord)-abs(y)) < 0.1*step
		{
			return true;
		}
	}
	return false;
}

bool Snake::SCheckSelfCollision()
{
	float x = SGetBlock(0).xcoord;
	float y = SGetBlock(0).ycoord;

	for (int i = 3; i <= length; i++)
	{
		if (abs(SGetBlock(i).xcoord - x) < 0.1*g.step && abs(SGetBlock(i).ycoord - y) < 0.1*g.step)
		{
			return true;
		}
	}
	return false;
}

bool Snake::SCheckWallCollision()
{
	float x = (float(g.width) /100.0) - 0.19; //temp value
	float y = (float(g.height) /100.0) - 0.19; //temp value


	//if (abs(Snake.SGetBlock(0).xcoord) - x < 0.2*step || abs(Snake.SGetBlock(0).ycoord) - y < 0.2*step)
	if (
		SGetBlock(0).xcoord > x ||
		SGetBlock(0).ycoord > y ||
		SGetBlock(0).xcoord < -x -g.step ||
		SGetBlock(0).ycoord < -y -g.step 
		)
	{
		return true;
	}

	return false;
}

bool Snake::SReset()
{

	block * next = start;
	
	//current = start->next;
	//MessageBox(NULL, _T(""), _T(""), NULL);
	while (next->next != NULL)
	{
		next = start->next;
		delete start;
		start = next;
	}
	Sleep(250);
	//MessageBox(NULL, _T(""), _T(""), NULL);
	start = new block;

	length = 0;
	start->xcoord = 0;
	start->ycoord = 0;
	start->xpast = 0;
	start->ypast = 0;
	start->next = NULL;
	SAddBlock();
	return true;
}

