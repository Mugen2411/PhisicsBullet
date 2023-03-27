#include "CProgressData.h"

#include <stdlib.h>
#include <windows.h>

#include "CDataLoader.h"
#include "CPassiveSkill.h"

CProgressData::CProgressData()
    : current_stage_(0),
      max_stage_(17),
      earned_money_(0),
      data_{0, 0, 0, 0},
      is_endless_(false),
      before_stage_(0xFF),
      dev_(),
      eng_(dev_()) {}

void CProgressData::Save() {
  FILE* fp;
  errno_t err = fopen_s(&fp, "media/save/0.sav", "wb");
  if (err != 0) {
    MessageBox(NULL, "セーブデータの作成に失敗しました", "MugenApp", MB_OK);
    return;
  }
  fclose(fp);
  auto c = CDataLoader::GetIns().Get("save")->GetChild("save");
  c->GetChild("money")->SetInt(data_.money);
  c->GetChild("level")->SetInt(data_.player_level_);
  c->GetChild("last_stage")->SetInt(data_.last_stage);
  c->GetChild("endless_last")->SetInt(data_.endless_last);
  c->GetChild("option")->SetInt(data_.is_option_flags);
  CDataLoader::GetIns().Save("save", "media/save/0.sav");
}

void CProgressData::Load() {
  FILE* fp;
  errno_t err = fopen_s(&fp, "media/save/0.sav", "rb");
  if (err != 0) {
    MessageBox(NULL, "セーブデータを新しく作成します", "MugenApp", MB_OK);
    CDataLoader::GetIns().Load("save", "media/save/null.sav");
    Save();
    return;
  }
  fclose(fp);
  CDataLoader::GetIns().Load("save", "media/save/0.sav");
  auto c = CDataLoader::GetIns().Get("save")->GetChild("save");
  data_.money = c->GetChild("money")->GetInt();
  data_.last_stage = c->GetChild("last_stage")->GetInt();
  data_.is_option_flags = c->GetChild("option")->GetInt();
  data_.endless_last = c->GetChild("endless_last")->GetInt();
  data_.player_level_ = c->GetChild("level")->GetInt();
}

void CProgressData::Win(int money) {
  earned_money_ = (int)std::ceil(money);
  stage_money_ = 100 * (int)std::ceil((current_stage_ + 1) *
                                      CPassiveSkill::GetIns().GetMoneyMult());
  data_.money += earned_money_;
  data_.money += stage_money_;
  if (!is_endless_)
    data_.last_stage = (std::min)(
        max_stage_ - 1, (std::max)(data_.last_stage, (current_stage_ + 1)));
  else {
    data_.endless_last =
        (std::max)(data_.last_stage, (current_stage_ + 1) / 10);
  }
}

void CProgressData::Lose(int money) {
  earned_money_ = (int)std::ceil(money);
  data_.money += earned_money_;
  if (!is_endless_)
    data_.last_stage = (std::min)(
        max_stage_ - 1, (std::max)(data_.last_stage, (current_stage_)));
  else {
    data_.endless_last =
        (std::max)(data_.last_stage, (current_stage_) / 10);
  }
}

void CProgressData::Retire(int money) {
  earned_money_ = (int)std::ceil(money);
  data_.money += earned_money_;
  if (!is_endless_)
    data_.last_stage = (std::min)(
        max_stage_ - 1, (std::max)(data_.last_stage, (current_stage_)));
  else {
    data_.endless_last = (std::max)(data_.last_stage, (current_stage_) / 10);
  }
}
