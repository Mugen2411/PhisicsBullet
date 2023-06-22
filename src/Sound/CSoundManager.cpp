#include "CSoundManager.h"

#include "Calc/CProgressData.h"

CSoundManager::CSoundManager() {
  sound_list_["player_dead"] =
      std::make_shared<CSound>("media/sound/se/player_dead.wav");
  sound_list_["player_hit"] =
      std::make_shared<CSound>("media/sound/se/player_hit.wav");
  sound_list_["enemy_kill"] =
      std::make_shared<CSound>("media/sound/se/enemy_kill.wav");
  sound_list_["enemy_hit"] =
      std::make_shared<CSound>("media/sound/se/enemy_hit.wav");
  sound_list_["shot_superball"] =
      std::make_shared<CSound>("media/sound/se/superball.wav");
  sound_list_["shot_cork"] = std::make_shared<CSound>("media/sound/se/cork.wav");
  sound_list_["cursor"] = std::make_shared<CSound>("media/sound/se/cursor.wav");
  sound_list_["money"] = std::make_shared<CSound>("media/sound/se/money.wav");
  sound_list_["success"] = std::make_shared<CSound>("media/sound/se/success.wav");
  sound_list_["bat_swing"] =
      std::make_shared<CSound>("media/sound/se/bat_swing.wav");
  sound_list_["throw"] = std::make_shared<CSound>("media/sound/se/throw.wav");
  sound_list_["glassBreak"] =
      std::make_shared<CSound>("media/sound/se/glassBreak.wav");
  sound_list_["little_fire"] =
      std::make_shared<CSound>("media/sound/se/little_fire.wav");
  sound_list_["little_magic"] =
      std::make_shared<CSound>("media/sound/se/little_magic.wav");
  sound_list_["middle_magic"] =
      std::make_shared<CSound>("media/sound/se/middle_magic.wav");
  sound_list_["pretty_throw"] =
      std::make_shared<CSound>("media/sound/se/pretty_throw.wav");
  sound_list_["splash"] = std::make_shared<CSound>("media/sound/se/splash.wav");

  sound_list_["bgm"] = std::make_shared<CSound>("media/sound/bgm/farm.ogg");
}

void CSoundManager::Unload() {
  for (auto& i : sound_list_) {
    i.second->Release();
  }
}

std::shared_ptr<CSound> CSoundManager::Find(std::string key) {
  auto itr = sound_list_[key];
  itr->Load();
  return itr;
}

void CSoundManager::LoadBGM(std::string path) {
  if (CProgressData::GetIns().GetFMorPCM()) {
    for (int i = 0; i < 4; i++) path.pop_back();
    path += "_FM.ogg";
  }
  sound_list_["bgm"] = std::make_shared<CSound>(path);
}
