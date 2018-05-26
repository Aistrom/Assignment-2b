#include "TimeKeeper.h"

float TimeKeeper::gameTimeElapsed = 0.0f;

float TimeKeeper::GetTimeFromStart()
{
	return gameTimeElapsed;
}

void TimeKeeper::Update(float timestep)
{
	gameTimeElapsed += timestep;
}