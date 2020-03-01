#include "GameTime.h"

void haha(int i)
{

}

GameTime::GameTime()
{
	lastFrame = Now;



	std::function< void()> PhysicsTimeUpdate = [&]() {

		while (true)
		{
			lastPhysicsTick = Now;
			std::this_thread::sleep_for(std::chrono::microseconds((int)(PhysicsTime * 1000.0f)));
		}
	};

	std::thread physicsTimeHandler(PhysicsTimeUpdate);
	physicsTimeHandler.detach();

}

GameTime::~GameTime()
{
}

float GameTime::TimeSinceLastFrame()
{
	Duration duration = std::chrono::duration_cast<MS>(Now - lastFrame);
	return duration.count();
}

float GameTime::TimeSinceGameBegining()
{
	Duration duration = std::chrono::duration_cast<MS>(Now - gameStart);
	return duration.count();
}

void GameTime::MarkEndOfFrame()
{
	lastFrame = Now;
}

void GameTime::ResetGameStart()
{
	gameStart = Now;
}

void GameTime::StallUntilNextPhysicsTick()
{
	Time stallBegining = Now;
	
	while (stallBegining >= lastPhysicsTick)
	{
		continue;
	}

}

void GameTime::StallFor(float stallDuration)
{
	Time stallBegining = Now;
	Duration duration = std::chrono::milliseconds(0);

	while (duration.count() <= (int) stallDuration)
	{
		duration = std::chrono::duration_cast<MS>(Now - stallBegining);
	}
}

bool GameTime::IsNewPhysicsCycle()
{
	if (lastPhysicsTick > lastPhysicsCheck)
	{
		lastPhysicsCheck = Now;
		return true;
	}
	else
	{
		lastPhysicsCheck = Now;
		return false;
	}
}

void GameTime::UpdatePhysicsTime()//Time *_lastPhysicsTick)
{
	//Duration duration;
		
	while (true)
	{
		/*duration = std::chrono::duration_cast<MS>(Now - lastPhysicsTick);
		if (duration.count() >= PhysicsTime)
		{
			lastPhysicsTick = Now;
			sleep
		}*/
		lastPhysicsTick = Now;
		std::this_thread::sleep_for(std::chrono::microseconds((int)(PhysicsTime * 1000.0f) ));
	}
}
