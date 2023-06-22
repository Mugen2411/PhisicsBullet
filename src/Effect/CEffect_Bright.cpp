#include "CEffect_Bright.h"

#include <DxLib.h>

#include "Graphic/CAnchor.h"

CEffect_Bright::CEffect_Bright() : bright_level_(0), active_(false) {
  bright_screen_ = MakeScreen(640, 480);
  shadow_screen_ = MakeScreen(640, 480);
  bright_buffer_ = MakeScreen(640, 480);
  shadow_buffer_ = MakeScreen(640, 480);
  bright_graph_ = LoadGraph("media/graphic/system/game/bright.png");
}

void CEffect_Bright::Render() const {
  SetDrawScreen(bright_screen_);
  ClearDrawScreen();
  SetDrawScreen(shadow_screen_);
  ClearDrawScreen();
  SetDrawScreen(bright_buffer_);
  ClearDrawScreen();
  SetDrawScreen(shadow_buffer_);
  ClearDrawScreen();
  if (!active_) {
    SetDrawScreen(offscreen_);
    return;
  }
  SetDrawScreen(bright_buffer_);
  int b = (int)max(0, bright_level_ * 0xFF);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  DrawBox(0, 0, 640, 480, GetColor(b, b, b), TRUE);
  for (auto& i : list_) {
    if (i.power < 0) continue;
    SetDrawBlendMode(DX_BLENDMODE_ADD, i.power);
    DrawRotaGraph((int)(i.position_.x_ - CAnchor::GetIns().GetAnchorX()),
                  (int)(i.position_.y_ - CAnchor::GetIns().GetAnchorY()),
                  i.radius / 256.0, 0, bright_graph_, TRUE);
  }

  SetDrawScreen(shadow_buffer_);
  b = (int)min(0, bright_level_ * 0xFF);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
  DrawBox(0, 0, 640, 480, GetColor(-b, -b, -b), TRUE);
  for (auto& i : list_) {
    if (i.power > 0) continue;
    SetDrawBlendMode(DX_BLENDMODE_ADD, -i.power);
    DrawRotaGraphF((float)(i.position_.x_ - CAnchor::GetIns().GetAnchorX()),
                  (float)(i.position_.y_ - CAnchor::GetIns().GetAnchorY()),
                  (float)i.radius / 256.0f, 0.0f, bright_graph_, TRUE);
  }
  SetDrawScreen(bright_screen_);
  SetDrawBlendMode(DX_BLENDMODE_ADD, 0xFF);
  DrawGraph(0, 0, bright_buffer_, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_SUB, 0xFF);
  DrawGraph(0, 0, shadow_buffer_, TRUE);

  SetDrawScreen(shadow_screen_);
  SetDrawBlendMode(DX_BLENDMODE_ADD, 0xFF);
  DrawGraph(0, 0, shadow_buffer_, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_SUB, 0xFF);
  DrawGraph(0, 0, bright_buffer_, TRUE);

  SetDrawScreen(offscreen_);
  SetDrawBlendMode(DX_BLENDMODE_SUB, 0xFF);
  DrawGraph(0, 0, shadow_screen_, TRUE);
  // SetDrawBlendMode(DX_BLENDMODE_ADD, 0xFF);
  // DrawGraph(0, 0, brightScreen, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}