#include "CEffect_Bright.h"

#include <DxLib.h>

#include "CAnchor.h"

CEffect_Bright::CEffect_Bright() : brightLevel(0), active(false) {
  brightScreen = MakeScreen(640, 480);
  shadowScreen = MakeScreen(640, 480);
  brightBuffer = MakeScreen(640, 480);
  shadowBuffer = MakeScreen(640, 480);
  brightGraph = LoadGraph("media/graphic/system/game/bright.png");
}

void CEffect_Bright::Render() const {
  SetDrawScreen(brightScreen);
  ClearDrawScreen();
  SetDrawScreen(shadowScreen);
  ClearDrawScreen();
  SetDrawScreen(brightBuffer);
  ClearDrawScreen();
  SetDrawScreen(shadowBuffer);
  ClearDrawScreen();
  if (!active) {
    SetDrawScreen(offscreen);
    return;
  }
  SetDrawScreen(brightBuffer);
  int b = (int)max(0, brightLevel * 0xFF);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  DrawBox(0, 0, 640, 480, GetColor(b, b, b), TRUE);
  for (auto& i : list) {
    if (i.power < 0) continue;
    SetDrawBlendMode(DX_BLENDMODE_ADD, i.power);
    DrawRotaGraph((int)(i.position.x - CAnchor::getIns().getAnchorX()),
                  (int)(i.position.y - CAnchor::getIns().getAnchorY()),
                  i.radius / 256.0, 0, brightGraph, TRUE);
  }

  SetDrawScreen(shadowBuffer);
  b = (int)min(0, brightLevel * 0xFF);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  DrawBox(0, 0, 640, 480, GetColor(-b, -b, -b), TRUE);
  for (auto& i : list) {
    if (i.power > 0) continue;
    SetDrawBlendMode(DX_BLENDMODE_ADD, -i.power);
    DrawRotaGraphF((float)(i.position.x - CAnchor::getIns().getAnchorX()),
                  (float)(i.position.y - CAnchor::getIns().getAnchorY()),
                  (float)i.radius / 256.0f, 0.0f, brightGraph, TRUE);
  }
  SetDrawScreen(brightScreen);
  SetDrawBlendMode(DX_BLENDMODE_ADD, 0xFF);
  DrawGraph(0, 0, brightBuffer, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_SUB, 0xFF);
  DrawGraph(0, 0, shadowBuffer, TRUE);

  SetDrawScreen(shadowScreen);
  SetDrawBlendMode(DX_BLENDMODE_ADD, 0xFF);
  DrawGraph(0, 0, shadowBuffer, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_SUB, 0xFF);
  DrawGraph(0, 0, brightBuffer, TRUE);

  SetDrawScreen(offscreen);
  SetDrawBlendMode(DX_BLENDMODE_SUB, 0xFF);
  DrawGraph(0, 0, shadowScreen, TRUE);
  // SetDrawBlendMode(DX_BLENDMODE_ADD, 0xFF);
  // DrawGraph(0, 0, brightScreen, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}