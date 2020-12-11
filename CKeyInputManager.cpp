#include "CKeyInputManager.h"
#include "Constant.h"

int CKeyInputManager::update()
{
	int r = 0;
	for (int i = 0; i < 9; i++) {
		if (CheckHitKey(KeyConfig[i]) == 1) {
			pushedFrame[i]++;
			if (SK_UP <= i && i <= SK_LEFT)r = 1;
		}
		else pushedFrame[i] = 0;
	}

	GetMousePoint(&mx, &my);
	if (mx < 16) {
		mx = 16;
		SetMousePoint(mx, my);
	}
	if (mx > Constant::ScreenW-16) {
		mx = Constant::ScreenW-16;
		SetMousePoint(mx, my);
	}
	if (my < 16) {
		my = 16;
		SetMousePoint(mx, my);
	}
	if (my > Constant::ScreenH-16) {
		my = Constant::ScreenH-16;
		SetMousePoint(mx, my);
	}
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
	//SetMouseDispFlag(FALSE);
}
