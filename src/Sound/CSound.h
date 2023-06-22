#pragma once
#include <DxLib.h>

#include <string>

class CSound {
 public:
  CSound(std::string path);

  inline void Load() {
    if (sound_handle_ == 0) {
      sound_handle_ = LoadSoundMem(filepath_.c_str());
      SetVolume(0.6);
    }
  }
  void Release();
  void Play(int PlayType);
  enum PlayType { kBack = DX_PLAYTYPE_BACK, kLoop = DX_PLAYTYPE_LOOP };
  void Stop();
  void SetVolume(double volume);  // 0.0~1.0

 private:
  int sound_handle_;
  std::string filepath_;
};
