#pragma once
#include "CGameMediator.h"
#include "Fps.h"

class CGame
{
	Fps fps;
	CGameMediator gameM;
public:
	CGame();
	void Run();
};

