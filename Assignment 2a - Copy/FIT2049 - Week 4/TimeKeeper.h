#ifndef TIME_KEEPER_H
#define TIME_KEEPER_H

class TimeKeeper
{
private:
	static float gameTimeElapsed;

public:
	static float GetTimeFromStart();
	static void Update(float timestep);
};

#endif