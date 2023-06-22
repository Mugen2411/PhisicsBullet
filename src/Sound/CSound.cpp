#include "CSound.h"

CSound::CSound(std::string path) : filepath_(path), sound_handle_(0) {}

void CSound::Release() { DeleteSoundMem(sound_handle_); }

void CSound::Play(int PlayType) { PlaySoundMem(sound_handle_, PlayType); }

void CSound::Stop() { StopSoundMem(sound_handle_); }

void CSound::SetVolume(double volume) {
  ChangeVolumeSoundMem(int(volume * 255), sound_handle_);
}
