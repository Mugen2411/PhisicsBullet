#pragma once
#include "CMover_ShotBase.h"
#include "CSoundManager.h"

class CMover_Shot_Festa_Superball : public CMover_ShotBase {
  int color_;
  int effect_color[4] = {0xFF0000, 0x00FFFF, 0x00FF00, 0xFFFF00};

 public:
  CMover_Shot_Festa_Superball(CAttribute baseATK, CVector position,
                              double angle);
  int Update();
  void Render() const;

  void IfOnWall() {
    CSoundManager::GetIns()
        .Find("shot_superball")
        ->Play(CSound::PlayType::kBack);
  };
};
