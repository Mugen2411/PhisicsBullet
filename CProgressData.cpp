#include "CProgressData.h"

#include <stdlib.h>
#include <windows.h>

#include "CPassiveSkill.h"

CProgressData::CProgressData()
    : currentStage(0),
      maxStage(11),
      earnedMoney(0),
      data{0, 0, 0},
      isEndless(false),
      beforeStage(0xFF),
      dev(),
      eng(dev()) {}

void CProgressData::save() {
  FILE* fp;
  errno_t err = fopen_s(&fp, "media/save/0.sav", "wb");
  if (err != 0) {
    MessageBox(NULL, "セーブデータの作成に失敗しました", "MugenApp", MB_OK);
    return;
  }
  fwrite(&data, sizeof(progressData), 1, fp);
  fclose(fp);
}

void CProgressData::load() {
  FILE* fp;
  errno_t err = fopen_s(&fp, "media/save/0.sav", "rb");
  if (err != 0) {
    MessageBox(NULL, "セーブデータを新しく作成します", "MugenApp", MB_OK);
    save();
    return;
  }
  fread(&data, sizeof(progressData), 1, fp);
  fclose(fp);
}

void CProgressData::win(int money) {
  earnedMoney = money * CPassiveSkill::getIns().getMoneyMult();
  stageMoney =
      400 * (currentStage + 1) * CPassiveSkill::getIns().getMoneyMult();
  data.Money += earnedMoney;
  data.Money += stageMoney;
  if (!isEndless)
    data.lastStage = (std::min)(maxStage - 1,
                                (std::max)(data.lastStage, (currentStage + 1)));
}

void CProgressData::lose(int money) {
  earnedMoney = money * CPassiveSkill::getIns().getMoneyMult();
  data.Money += earnedMoney;
  if (!isEndless)
    data.lastStage =
        (std::min)(maxStage - 1, (std::max)(data.lastStage, (currentStage)));
}

void CProgressData::retire(int money) {
  earnedMoney = money * CPassiveSkill::getIns().getMoneyMult();
  data.Money += earnedMoney;
  if (!isEndless)
    data.lastStage =
        (std::min)(maxStage - 1, (std::max)(data.lastStage, (currentStage)));
}
