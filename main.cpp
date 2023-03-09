#include <DxLib.h>

#include "CEffect_Bright.h"
#include "CImageManager.h"
#include "CProgressData.h"
#include "CSoundManager.h"
#include "Clooper.h"
#include "CDataLoader.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
  //setlocale(LC_CTYPE, "ja_JP.UTF-8");
  CDataLoader::GetIns().Load("media/status/params.mgs");
  //CDataLoader::GetIns().Output();
  ChangeWindowMode(TRUE);
  SetWindowText("Makeover trial");
  SetOutApplicationLogValidFlag(FALSE);
  SetWindowIconID(101);
  CProgressData::GetIns().Load();
  int WindowExtendRate = 1 + CProgressData::GetIns().GetWindowX2();
  SetGraphMode(640 * WindowExtendRate, 480 * WindowExtendRate, 32);
  if (DxLib_Init() != 0) return -1;
  // SetAlwaysRunFlag(TRUE);
  // SetWaitVSyncFlag(FALSE);
  CGame g = CGame();
  SetBackgroundColor(0, 0, 0, 0);
  SetLogFontHandle(
      CreateFontToHandle("MS P Gothic", 24, 4, DX_FONTTYPE_ANTIALIASING_EDGE));
  int offscreen = MakeScreen(640, 480);
  CEffect_Bright::GetIns().SetOffScreen(offscreen);
  SetDrawMode(DX_DRAWMODE_BILINEAR);
  SetDrawScreen(offscreen);
  while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && clsDx() == 0) {
    g.Run();
    SetDrawMode(DX_DRAWMODE_NEAREST);
    SetDrawScreen(DX_SCREEN_BACK);
    ClearDrawScreen();
    DrawExtendGraph(0, 0, 640 * WindowExtendRate, 480 * WindowExtendRate,
                    offscreen, FALSE);
    ScreenFlip();
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    SetDrawScreen(offscreen);
    if (g.IsQuitted()) break;
  }
  CProgressData::GetIns().Save();
  CImageManager::GetIns().Unload();
  CSoundManager::GetIns().Unload();
  DxLib_End();
  return 0;
}