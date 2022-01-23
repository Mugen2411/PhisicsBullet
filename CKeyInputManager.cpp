#include "CKeyInputManager.h"
#include "Constant.h"

int CKeyInputManager::isChanged()
{
	return changed;
}

int CKeyInputManager::update()
{
	int r = 0;
	for (int i = 0; i < 10; i++) {
		if (CheckHitKey(KeyConfig[i])) {
			pushedFrame[i]++;
			if (SK_UP <= i && i <= SK_LEFT)r = 1;
		}
		else pushedFrame[i] = 0;
#ifdef _DEBUG
		printfDx("%d:%d\n", i, pushedFrame[i]);
#endif
	}
	changed = r;

	int nx, ny;
	GetMousePoint(&nx, &ny);
	mx += (nx - (Constant::ScreenW / 2)) / 2;
	my += (ny - (Constant::ScreenH / 2)) / 2;
	if (mx < 0)mx = 0;
	if (mx > Constant::ScreenW)mx = Constant::ScreenW;
	if (my < 0)my = 0;
	if (my > Constant::ScreenH)my = Constant::ScreenH;
	SetMousePoint(Constant::ScreenW / 2, Constant::ScreenH / 2);

	int mi = GetMouseInput();
	if (mi & MOUSE_INPUT_LEFT) {
		clickedFrame[0][1]++;
		clickedFrame[0][0] = 0;
	}
	else {
		clickedFrame[0][0]++;
		clickedFrame[0][1] = 0;
	}
	if (mi & MOUSE_INPUT_RIGHT) {
		clickedFrame[1][1]++;
		clickedFrame[1][0] = 0;
	}
	else {
		clickedFrame[1][0]++;
		clickedFrame[1][1] = 0;
	}
	if (mi & MOUSE_INPUT_MIDDLE) {
		clickedFrame[2][1]++;
		clickedFrame[2][0] = 0;
	}
	else {
		clickedFrame[2][0]++;
		clickedFrame[2][1] = 0;
	}

	return r;
}

void CKeyInputManager::load()
{
	if(GetActiveFlag())SetMousePoint(Constant::ScreenW / 2, Constant::ScreenH / 2);
	SetMouseDispFlag(FALSE);
}
