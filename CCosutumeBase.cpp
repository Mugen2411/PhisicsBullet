#include "CCosutumeBase.h"

#include "CDataLoader.h"
#include "CImageManager.h"
#include "CMover_Player.h"

CCostumeBase::CCostumeBase(std::string gid_)
    : animation_speed_(0),
      max_charge_(0),
      shot_rate_(0),
      strong_shot_duration_(0),
      max_speed_(0),
      accel_(0),
      mass_(0),
      attribute_def_(CAttribute(0)),
      player_ptr_(nullptr),
      cofs_(COF()),
      gid_(gid_) {
  LoadStatus();
}

void CCostumeBase::RegisterShot(std::shared_ptr<CMover_ShotBase> s) {
  player_ptr_->RegisterShot(s);
}

void CCostumeBase::LoadStatus() {
  auto d = CDataLoader::GetIns().Get();
  auto e = d->GetChild("costume")->GetChild(gid_);
  graph_filepath_ =
      std::string("media/graphic/character/komuk/costume/") +
      e->GetChild("graph")->GetString();
  CImageManager::GetIns().Set(
      gid_, std::make_shared<CImage>(graph_filepath_, 16, 4, 4, 32, 32));
  animation_speed_ = e->GetChild("animSpd")->GetDouble();
  mass_ = e->GetChild("mass")->GetInt();
  max_charge_ = e->GetChild("maxChg")->GetInt();
  shot_rate_ = e->GetChild("shotRt")->GetInt();
  strong_shot_duration_ = e->GetChild("stDur")->GetInt();
  max_speed_ = e->GetChild("spd")->GetDouble();
  accel_ = e->GetChild("acl")->GetDouble();
  attribute_def_.Load(e->GetChild("atrd"));
  cofs_.Load(e->GetChild("cof"));
  detail_ = CTextDrawer::Text(e->GetChild("detail")->GetString(),
                              Constant::kCostumeDetailPosition, 0xFFFFFF,
                              0x000000, 0);
}
