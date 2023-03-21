#include "CProgressData.h"

#include <stdlib.h>
#include <windows.h>

#include "CPassiveSkill.h"

CProgressData::CProgressData()
    : current_stage_(0),
      max_stage_(17),
      earned_money_(0),
      data_{0, 0, 0},
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
  fwrite(&data_, sizeof(ProgressData), 1, fp);
  fclose(fp);
}

void CProgressData::Load() {
  FILE* fp;
  errno_t err = fopen_s(&fp, "media/save/0.sav", "rb");
  if (err != 0) {
    MessageBox(NULL, "セーブデータを新しく作成します", "MugenApp", MB_OK);
    Save();
    return;
  }
  fread(&data_, sizeof(ProgressData), 1, fp);
  fclose(fp);
}

void CProgressData::Win(int money) {
  earned_money_ = (int)std::ceil(money);
  stage_money_ =
      100 * (int)std::ceil((current_stage_ + 1) * CPassiveSkill::GetIns().GetMoneyMult());
  data_.money += earned_money_;
  data_.money += stage_money_;
  if (!is_endless_)
    data_.last_stage = (std::min)(max_stage_ - 1,
                                (std::max)(data_.last_stage, (current_stage_ + 1)));
}

void CProgressData::Lose(int money) {
  earned_money_ = (int)std::ceil(money);
  data_.money += earned_money_;
  if (!is_endless_)
    data_.last_stage =
        (std::min)(max_stage_ - 1, (std::max)(data_.last_stage, (current_stage_)));
}

void CProgressData::Retire(int money) {
  earned_money_ = (int)std::ceil(money);
  data_.money += earned_money_;
  if (!is_endless_)
    data_.last_stage =
        (std::min)(max_stage_ - 1, (std::max)(data_.last_stage, (current_stage_)));
}
