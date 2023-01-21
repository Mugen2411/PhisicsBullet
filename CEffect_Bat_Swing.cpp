#include "CEffect_Bat_Swing.h"

#include "CImageManager.h"

CEffect_Bat_Swing::CEffect_Bat_Swing(CVector position, double angle)
    : CEffect(position), angle(angle), cnt(0) {}

void CEffect_Bat_Swing::Update() {
  cnt++;
  if (cnt > 16) Status = 1;
}

void CEffect_Bat_Swing::Render() const {
  CImageManager::getIns()
      .find("effect_bat")
      ->DrawRotaF(Position.x + min(cnt, 8) * 8 * cos(angle),
                  Position.y + min(cnt, 8) * 8 * sin(angle), angle,
                  min(cnt, 8) / 8.0, Constant::priority_shot);
  if (cnt <= 8)
    CImageManager::getIns()
        .find("effect_bathead")
        ->DrawRotaF(Position.x + min(cnt, 8) * 16 * cos(angle),
                    Position.y + min(cnt, 8) * 16 * sin(angle), angle,
                    2.0 - min(cnt, 8) / 8.0, Constant::priority_shot + 1);
}
