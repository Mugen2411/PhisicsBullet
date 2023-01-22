#pragma once
#include <memory>
#include <unordered_map>

#include "CSound.h"
#include "Singleton.h"

class CSoundManager : public Singleton<CSoundManager> {
 public:
  void Unload();
  std::shared_ptr<CSound> Find(std::string key);
  void LoadBGM(std::string path);

 private:
  std::unordered_map<std::string, std::shared_ptr<CSound>> sound_list_;
  CSoundManager();

  friend class Singleton<CSoundManager>;
};
