#include "CEffect_Wind.h"

#include <DxLib.h>

#include "CImageManager.h"

CEffect_Wind::CEffect_Wind(CVector position, double power, float angle,
                           double width, double length)
    : CEffect(position),
      basePos(position),
      duration((int)(length / power / 0.25f)),
      power(power * 0.25f),
      width(width),
      length(length),
      delta(GetRand(100) * 0.01f * (float)Constant::PI2),
      angle(angle),
      x(0),
      y(0),
      z(0) {}

void CEffect_Wind::Update() {
  if (cnt > duration) {
    Status = 1;
    return;
  }
  z = (float)(Constant::PI2 * Constant::perFrame * (duration / 4) * cnt);
  x = cosf(z + delta) * (float)width * 0.5f;
  y = cnt * (float)power;
  z = (sinf(z + delta) + 1.0f) * 0.5f;
  Position.x = cos(angle) * y + cos(angle + Constant::PI / 2) * x;
  Position.y = sin(angle) * y + sin(angle + Constant::PI / 2) * x;
  Position += basePos;
  cnt++;
}

void CEffect_Wind::Render() const {
  CImageManager::getIns()
      .find("effect_wind")
      ->DrawRotaFwithBlend(
          Position.x, Position.y, angle,
          ((float)(duration - cnt) / duration * 0.5f + 0.5f) / 4.0f, 0xFFFFFF,
          CImageManager::BLENDMODE::BM_ALPHA, int(z * 0xFF),
          Constant::priority_effect, 1);
}
