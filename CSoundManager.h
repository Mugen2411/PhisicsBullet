#pragma once
#include <memory>
#include <unordered_map>

#include "CSound.h"
#include "Singleton.h"

class CSoundManager : public Singleton<CSoundManager> {
  std::unordered_map<std::string, std::shared_ptr<CSound>> sndList;
  CSoundManager();

 public:
  void unload();
  std::shared_ptr<CSound> find(std::string key);
  void LoadBGM(std::string path);

  friend class Singleton<CSoundManager>;
};
