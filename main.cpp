#include <DxLib.h>
#include "Clooper.h"
#include "CRenderReserveList.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	ChangeWindowMode(TRUE);
	//SetWindowSizeExtendRate(2.0);
	SetGraphMode(640 * 2, 480 * 2, 32);
	if (DxLib_Init() != 0)return -1;
	SetAlwaysRunFlag(TRUE);
	//SetWaitVSyncFlag(FALSE);
	CGame g = CGame();
	int offscreen = MakeScreen(640, 480);
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && clsDx() == 0 && !CheckHitKey(KEY_INPUT_TAB)) {
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		SetDrawScreen(offscreen);
		g.Run();
		CRenderReserveList::Render();
		SetDrawScreen(DX_SCREEN_BACK);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawExtendGraph(0, 0, 640 * 2, 480 * 2, offscreen, FALSE);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}