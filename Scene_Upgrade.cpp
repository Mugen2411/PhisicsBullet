#include "Scene_Upgrade.h"

#include <cassert>

#include "CAnchor.h"
#include "CControllerFactory.h"
#include "CImageManager.h"
#include "CProgressData.h"
#include "CSoundManager.h"
#include "CStatus.h"

Scene_Upgrade::Scene_Upgrade(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng),
      has_enough_money_(true),
      cnt_(0),
      now_(CProgressData::GetIns().GetPlayerLevel()),
      next_(CProgressData::GetIns().GetPlayerLevel() + 1) {
  input_ = CControllerFactory::GetIns().GetController();
  text_[0] = CTextDrawer::Text("�A�b�v�O���[�h", CVector(320 - 3.5 * 60, 32.0),
                              0xFFFFFF, 0x7F7F00, 2);
  text_[1] = CTextDrawer::Text("�����R�C��", CVector(320 - 36 * 5, 120),
                              0xFFFFFF, 0xCFCF00, 1);
  text_[2] = CTextDrawer::Text("�K�v�R�C��", CVector(320 - 36 * 5, 160),
                              0xFFFFFF, 0xCFCF00, 1);
  text_[3] = CTextDrawer::Text("���݂̃X�e�[�^�X", CVector(320 - 200, 240),
                              0xFFFFFF, 0xCFCF00, 0);
  text_[4] = CTextDrawer::Text("������X�e�[�^�X", CVector(320 - 200, 270),
                              0xFFFFFF, 0xCFCF00, 0);
  text_[5] =
      CTextDrawer::Text("SPACE�L�[�������ƃR�C��������ċ������܂��B",
                        CVector(320 - 10 * 12, 320), 0xFFFFFF, 0x00CFCF, 0);
  text_[6] =
      CTextDrawer::Text("�R�C��������܂���I", CVector(320 - 5 * 36, 360),
                        0xFFFFFF, 0xFF0000, 1);
  CSoundManager::GetIns().Find("money")->SetVolume(0.5);
  CSoundManager::GetIns().Find("player_hit")->SetVolume(0.5);
}

void Scene_Upgrade::Update() {
  now_ = CStatus(CProgressData::GetIns().GetPlayerLevel());
  next_ = CStatus(CProgressData::GetIns().GetPlayerLevel() + 1);
  text_[1].text_ = std::string("�����R�C���F") +
                 std::to_string(CProgressData::GetIns().GetMoney());
  text_[2].text_ = std::string("�K�v�R�C���F") +
                 std::to_string(CStatus::GetMoneyToUpgrade(
                     CProgressData::GetIns().GetPlayerLevel()));
  text_[3].text_ = std::string("���݂̃X�e�[�^�X��") + std::string("HP:") +
                 FloatToString(now_.maxHP_) + std::string(" ATK:") +
                 FloatToString(now_.atk_);
  text_[4].text_ = std::string("������X�e�[�^�X��") + std::string("HP:") +
                 FloatToString(next_.maxHP_) + std::string(" ATK:") +
                 FloatToString(next_.atk_);

#ifndef _DEBUG
  if (input_.lock()->Select() == 1) {
    if (CProgressData::GetIns().GetMoney() >=
        CStatus::GetMoneyToUpgrade(CProgressData::GetIns().GetPlayerLevel())) {
      CProgressData::GetIns().Upgrade(
          CStatus::GetMoneyToUpgrade(CProgressData::GetIns().GetPlayerLevel()));
      has_enough_money_ = true;
      CSoundManager::GetIns().Find("money")->Play(CSound::PlayType::kBack);
    } else {
      CSoundManager::GetIns()
          .Find("player_hit")
          ->Play(CSound::PlayType::kBack);
      has_enough_money_ = false;
    }
  }
#endif

#ifdef _DEBUG
  if (input_.lock()->Select() == 1) {
    CProgressData::GetIns().Upgrade(0);
    has_enough_money_ = true;
    CSoundManager::GetIns().Find("money")->Play(CSound::PlayType::kBack);
  }
  if (input_.lock()->A() == 1) {
    CProgressData::GetIns().Degrade();
    has_enough_money_ = true;
    CSoundManager::GetIns().Find("money")->Play(CSound::PlayType::kBack);
  }
#endif

  if (input_.lock()->Start() == 1) {
    CProgressData::GetIns().Save();
    scene_manager_->PopScene();
    return;
  }
}

void Scene_Upgrade::Render() const {
  assert(text_[0].position_.y < 40.0);
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns().Find("system_curtain")->Draw(0, 0, 100, 0);
  CImageManager::GetIns().Find("system_curtain")->Draw(320, 0, 100, 1);
  for (int i = 0; i < 6; i++) {
    CTextDrawer::GetIns().Register(text_[i]);
  }
  if (!has_enough_money_) CTextDrawer::GetIns().Register(text_[6]);
  CImageManager::GetIns().Find("icon_return")->Draw(0, 0, 101);
  CAnchor::GetIns().DisableAbsolute();
}
