#pragma once
#include <DxLib.h>
#include <string>

class CSound
{
	int SHandle;
	std::string path;
public:
	CSound(std::string path);

	inline void Load() {
		if (SHandle == 0) {
			SHandle = LoadSoundMem(path.c_str());
		}
	}
	void Release();
	void Play(int PlayType);
	enum PLAYTYPE {
		PT_BACK = DX_PLAYTYPE_BACK,
		PT_LOOP = DX_PLAYTYPE_LOOP
	};
	void Stop();
	void SetVolume(double volume);	//0.0~1.0
};

