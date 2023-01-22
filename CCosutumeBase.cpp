#include "CCosutumeBase.h"

#include "CImageManager.h"
#include "CMover_Player.h"

CCostumeBase::CCostumeBase(std::string filepath, double animSpeed,
                           int MaxCharge, int ShotRate, int strongshotDuration,
                           double maxSpeed, double accel, double mass,
                           CAttribute attrDEF, COF constants, std::string gid_)
    : animation_speed_(animSpeed),
      max_charge_(MaxCharge),
      shot_rate_(ShotRate),
      strong_shot_duration_(strongshotDuration),
      max_speed_(maxSpeed),
      accelaration_(accel),
      mass_(mass),
      attribute_def_(attrDEF),
      player_ptr_(nullptr),
      constants_(constants),
      gid_(gid_) {
  graph_filepath_ = filepath;
  CImageManager::GetIns().Set(
      gid_, std::make_shared<CImage>(graph_filepath_, 16, 4, 4, 32, 32));
}

void CCostumeBase::RegisterShot(std::shared_ptr<CMover_ShotBase> s) {
  player_ptr_->RegisterShot(s);
}
