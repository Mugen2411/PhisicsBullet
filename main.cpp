#include <DxLib.h>
#include "Clooper.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	ChangeWindowMode(TRUE);
	SetWindowSizeExtendRate(2.0);
	if (DxLib_Init() != 0)return -1;
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawScreen(DX_SCREEN_BACK);
	//SetAlwaysRunFlag(TRUE);
	//SetWaitVSyncFlag(FALSE);
	CGame g = CGame();
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && clsDx() == 0 && !CheckHitKey(KEY_INPUT_TAB)) {
		g.Run();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}