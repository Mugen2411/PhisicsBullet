#include <DxLib.h>

#include "Data/CDataLoader.h"
#include "Effect/CEffect_Bright.h"
#include "Graphic/Image/CImageManager.h"
#include "Calc/CProgressData.h"
#include "Sound/CSoundManager.h"
#include "Clooper.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
  //setlocale(LC_ALL, "ja_JP.SJIS");
  CDataLoader::GetIns().Load("main", "media/status/params.mgs");
  CDataLoader::GetIns().Load("resource", "media/status/resource.mgs");
  CDataLoader::GetIns().Load("field", "media/status/field.mgs");
  ChangeWindowMode(TRUE);
  SetWindowText("Makeover");
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