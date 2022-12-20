#include "CProgressData.h"
#include <stdlib.h>
#include <windows.h>

CProgressData::CProgressData() :currentStage(0), maxStage(10), earnedMoney(0), data{0,0,0} {
}

void CProgressData::save()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "media/save/0.sav", "wb");
	if (err != 0) {
		MessageBox(NULL, "セーブデータの作成に失敗しました", "MugenApp", MB_OK);
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
		MessageBox(NULL, "セーブデータを新しく作成します", "MugenApp", MB_OK);
		save();
		return;
	}
	fread(&data, sizeof(progressData), 1, fp);
	fclose(fp);
}

void CProgressData::win(int money)
{
	earnedMoney = money;
	stageMoney = 400 * (currentStage+1);
	data.Money += earnedMoney;
	data.Money += stageMoney;
	data.lastStage = (std::min)(maxStage-1, (std::max)(data.lastStage, (currentStage+1)));
}

void CProgressData::lose(int money)
{
	earnedMoney = money;
	data.Money += earnedMoney;
	data.lastStage = (std::min)(maxStage-1, (std::max)(data.lastStage, (currentStage)));
}

void CProgressData::retire(int money)
{
	earnedMoney = money;
	data.Money += earnedMoney;
	data.lastStage = (std::min)(maxStage-1, (std::max)(data.lastStage, (currentStage)));
}

