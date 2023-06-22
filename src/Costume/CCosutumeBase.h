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
  CAttribute attribute_def_;  //�����ϐ�
  COF cofs_;            //�e�함���萔
  double mass_;
  double animation_speed_;  //���t���[��������
  int max_charge_;     //���ߎˌ��ɕK�v�Ȏ���(���t���[��+1)
  int shot_rate_;      //�A�˂����t���[�����ƂɌ���
  int strong_shot_duration_;  //���U������������ɑ���s�\�ɂȂ�t���[����
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
  CMover_Player* player_ptr_;    //�v���C���[�ւ̃|�C���^
  std::string graph_filepath_;  //�摜�t�@�C���̃p�X
  void LoadStatus();
};
