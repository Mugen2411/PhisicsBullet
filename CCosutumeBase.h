#pragma once
#include <memory>
#include <string>

#include "CAttribute.h"
#include "CMover_ShotBase.h"
#include "CSTGInputManager.h"
#include "CStatus.h"
#include "CTextDrawer.h"

class CMover_Player;

class CCostumeBase {
 public:
  CAttribute attribute_def_;  //�����ϐ�
  COF constants_;            //�e�함���萔
  const double mass_;
  const double animation_speed_;  //���t���[��������
  const int max_charge_;     //���ߎˌ��ɕK�v�Ȏ���(���t���[��+1)
  const int shot_rate_;      //�A�˂����t���[�����ƂɌ���
  const int strong_shot_duration_;  //���U������������ɑ���s�\�ɂȂ�t���[����
  const double max_speed_;
  const double accelaration_;
  const std::string gid_;
  CTextDrawer::Text detail_;

  CCostumeBase(std::string filepath, double animSpeed, int MaxCharge,
               int ShotRate, int strongshotDuration, double maxSpeed,
               double accel, double mass, CAttribute attrDEF, COF constants,
               std::string gid_);
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
};
