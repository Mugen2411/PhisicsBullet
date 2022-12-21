#include <DxLib.h>
#include "Clooper.h"
#include "CSoundManager.h"
#include "CImageManager.h"
#include "CProgressData.h"
#include "CEffect_Bright.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	ChangeWindowMode(TRUE);
	SetWindowText("Makeover trial");
	SetOutApplicationLogValidFlag(FALSE);
	SetWindowIconID(101);
	CProgressData::getIns().load();
	int WindowExtendRate = 1 + CProgressData::getIns().getWindowX2();
	SetGraphMode(640 * WindowExtendRate, 480 * WindowExtendRate, 32);
	if (DxLib_Init() != 0)return -1;
	//SetAlwaysRunFlag(TRUE);
	//SetWaitVSyncFlag(FALSE);
	CGame g = CGame();
	SetBackgroundColor(0,0,0,0);
	SetLogFontHandle(CreateFontToHandle("MS P Gothic", 24, 4, DX_FONTTYPE_ANTIALIASING_EDGE));
	int offscreen = MakeScreen(640, 480);
	CEffect_Bright::getIns().setOffScreen(offscreen);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawScreen(offscreen);
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && clsDx() == 0 && !CheckHitKey(KEY_INPUT_TAB)) {
		g.Run();
		SetDrawMode(DX_DRAWMODE_NEAREST);
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(0, 0, 640 * WindowExtendRate, 480 * WindowExtendRate, offscreen, FALSE);
		ScreenFlip();
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		SetDrawScreen(offscreen);
		if (g.isQuitted())break;
	}
	CProgressData::getIns().save();
	CImageManager::getIns().unload();
	CSoundManager::getIns().unload();
	DxLib_End();
	return 0;
}