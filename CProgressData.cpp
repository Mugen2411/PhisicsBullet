#include "CProgressData.h"
#include <stdlib.h>
#include <windows.h>

CProgressData::CProgressData() :currentStage(0), maxStage(2), data{ maxStage,0,0 } {
}

void CProgressData::save()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "media/save/0.sav", "wb");
	if (err != 0) {
		MessageBox(NULL, "�Z�[�u�f�[�^�̍쐬�Ɏ��s���܂���", "MugenApp", MB_OK);
		return;
	}
	fwrite(&data, sizeof(progressData), 1, fp);
	fclose(fp);
}

void CProgressData::load()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "media/save/0.sav", "rb");
	if (err != 0) {
		MessageBox(NULL, "�Z�[�u�f�[�^��V�����쐬���܂�", "MugenApp", MB_OK);
		return;
	}
	fread(&data, sizeof(progressData), 1, fp);
	fclose(fp);
}

void CProgressData::win(int money)
{
	data.Money += money;
	data.lastStage = (std::max)(data.lastStage, currentStage / 10);
}

void CProgressData::lose(int money)
{
	data.Money += money * 0.5;
	data.lastStage = (std::max)(data.lastStage, (currentStage - 1) / 10);
}

void CProgressData::retire(int money)
{
	data.Money += money;
	data.lastStage = (std::max)(data.lastStage, (currentStage - 1) / 10);
}

