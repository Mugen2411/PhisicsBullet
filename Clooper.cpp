#include "Clooper.h"

CGame::CGame():gameM(),fps()
{
}

void CGame::Run()
{
	gameM.Update();
	gameM.Render();
	fps.Update();
	fps.Draw();
	fps.Wait();
}
