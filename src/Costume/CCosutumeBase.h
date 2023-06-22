#pragma once
#include <memory>
#include <string>

#include "Calc/CAttribute.h"
#include "Mover/Shot/CMover_ShotBase.h"
#include "Input/CSTGInputManager.h"
#include "Calc/CStatus.h"
#include "Graphic/Draw/CTextDrawer.h"

class CMover_Player;

class CCostumeBase {
 public:
  CAttribute attribute_def_;  //属性耐性
  COF cofs_;            //各種物理定数
  double mass_;
  double animation_speed_;  //毎フレーム足す量
  int max_charge_;     //溜め射撃に必要な時間(毎フレーム+1)
  int shot_rate_;      //連射を何フレームごとに撃つか
  int strong_shot_duration_;  //強攻撃を撃った後に操作不能になるフレーム数
  double max_speed_;
  double accel_;
  const std::string gid_;
  CTextDrawer::Text detail_;

  CCostumeBase(std::string gid_);
  virtual ~CCostumeBase() {}

  virtual void ChargeShot(CAttribute baseATK, CVector position_,
                          float angle) = 0;
  virtual void WeakShot(CAttribute baseATK, CVector position_, float angle) = 0;

  void SetPlayer(CMover_Player* p) { player_ptr_ = p; }
  void RegisterShot(std::shared_ptr<CMover_ShotBase>);

  virtual CCostumeBase* Clone() = 0;

 protected:
  CMover_Player* player_ptr_;    //プレイヤーへのポインタ
  std::string graph_filepath_;  //画像ファイルのパス
  void LoadStatus();
};
