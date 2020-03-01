#pragma once
#include "Universal.h"

#define Time std::chrono::high_resolution_clock::time_point
#define Duration std::chrono::milliseconds//::duration
#define Now std::chrono::high_resolution_clock::now()
#define MS std::chrono::milliseconds
class GameTime
{
public:
	GameTime();
	~GameTime();

	float TimeSinceLastFrame(); //Returns time since last frame in ms
	float TimeSinceGameBegining(); //Returns time since game begining in ms
	void MarkEndOfFrame(); //call at the end of UpdateGame();
	void ResetGameStart();
	
	void StallUntilNextPhysicsTick();
	void StallFor(float);

	bool IsNewPhysicsCycle();

private:
	void UpdatePhysicsTime();// Time *); //Useless?


	Time gameStart;
	Time gameEnd;
	Time lastFrame;
	Time lastPhysicsTick;
	Time lastPhysicsCheck;
};