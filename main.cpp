#include <DxLib.h>
#include "Clooper.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	ChangeWindowMode(TRUE);
	//SetWindowSizeExtendRate(2.0);
	SetGraphMode(640 * 2, 480 * 2, 32);
	if (DxLib_Init() != 0)return -1;
	SetAlwaysRunFlag(TRUE);
	//SetWaitVSyncFlag(FALSE);
	CGame g = CGame();
	SetLogFontHandle(CreateFontToHandle("MS P Gothic", 24, 4, DX_FONTTYPE_ANTIALIASING_EDGE));
	int offscreen = MakeScreen(640, 480);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawScreen(offscreen);
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && clsDx() == 0 && !CheckHitKey(KEY_INPUT_TAB)) {
		g.Run();
		SetDrawMode(DX_DRAWMODE_NEAREST);
		SetDrawScreen(DX_SCREEN_BACK);
		DrawExtendGraph(0, 0, 640 * 2, 480 * 2, offscreen, FALSE);
		ScreenFlip();
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		SetDrawScreen(offscreen);
	}
	DxLib_End();
	return 0;
}