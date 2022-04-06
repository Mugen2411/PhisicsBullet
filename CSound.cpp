#include "CSound.h"

CSound::CSound(std::string path):path(path),SHandle(0)
{
}

void CSound::Release()
{
	DeleteSoundMem(SHandle);
}

void CSound::Play(int PlayType)
{
	PlaySoundMem(SHandle, PlayType);
}

void CSound::Stop()
{
	StopSoundMem(SHandle);
}

void CSound::SetVolume(double volume)
{
	ChangeVolumeSoundMem(volume * 255, SHandle);
}
