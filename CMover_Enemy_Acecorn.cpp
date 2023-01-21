#include "CMover_Enemy_Acecorn.h"

#include "CImageManager.h"
#include "CMover_Bullet_Corn.h"
#include "CNumberDrawer.h"
#include "CSoundManager.h"

CMover_Enemy_Acecorn::CMover_Enemy_Acecorn(CVector position, int Level)
    : CMover_EnemyBase(30, Level, 1.35, 3.2,
                       CAttribute(1.0).FIRE(0.5).FLOWER(3.0).AQUA(0.8), 80,
                       0xFF7F00, position, 4.8, 2.4, COF(0.8, 0.95, 0.06, 0.1)),
      testDest(0.0, 0.0),
      focus(0.0) {}

int CMover_Enemy_Acecorn::Update() {
  switch (state) {
    case 0:
      if (cnt % 60 == 0) {
        if (GetRand(5) == 0) {
          cnt = 0;
          findTargetByDistance(8);
          state = 2;
          return Status;
        } else
          Find_Route(3);
      }
      if (!route.empty()) {
        Move_on_Route();
      } else {
        CVector ppos = med->GetPlayerPosition();
        focus = (ppos - Position).getAngle();
        cnt = 0;
        state = 1;
        break;
      }
      cnt++;
      animCount += 0.3;
      if (animCount > 4) animCount = 0;
      break;
    case 1:
      if (cnt == 10) {
        med->RegisterMover(std::make_shared<CMover_Bullet_Corn>(
            baseParams, Position, focus, 6.0));
        CSoundManager::getIns()
            .find("pretty_throw")
            ->Play(CSound::PLAYTYPE::PT_BACK);
      }
      if (cnt > 20) {
        state = 0;
        cnt = 0;
        break;
      }
      animCount += 0.3;
      if (animCount > 4) animCount = 0;
      cnt++;
      break;
    case 2:
      if (!route.empty()) {
        Move_on_Route();
      } else {
        CVector ppos = med->GetPlayerPosition();
        focus = (ppos - Position).getAngle();
        for (int i = 0; i < 12; i++) {
          med->RegisterMover(std::make_shared<CMover_Bullet_Corn>(
              baseParams, Position, focus + Constant::PI2 / 12 * i, 6.5));
        }
        cnt = 0;
        state = 0;
      }
      cnt++;
      break;
    case -1:
      animCount += 0.1;
      if (animCount > 4) {
        state = 0;
        Find_Route(3);
        animCount = 0;
        cnt = 0;
      }
      break;
  }
  return Status;
}

void CMover_Enemy_Acecorn::Render() const {
  if (state < 0) {
    CImageManager::getIns()
        .find("enemy_bud_intro")
        ->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy,
                   (int)(animCount));
    return;
  }
  CImageManager::getIns()
      .find("enemy_acecorn")
      ->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_enemy,
                 Direction * 4 + (int)(animCount));
}

CMover_EnemyBase* CMover_Enemy_Acecorn::Clone(CVector Position, int Level) {
  return new CMover_Enemy_Acecorn(Position, Level);
}
