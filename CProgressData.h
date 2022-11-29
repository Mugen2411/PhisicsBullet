#pragma once
#include "Singleton.h"
#include <algorithm>
#include <string>

class CProgressData : public Singleton<CProgressData> {
public:

	void save();
	void load();

	void setCurrentStage(int stage) {	//次に入るステージ(Mediatorから設定)
		currentStage = (std::min)(stage, maxStage);
	}
	int getLastStage()		//今までに進んだ最大のステージ
	{
		return lastStage;
	}

	int getCurrentStage()	//次に入るステージ(Mediatorから参照)
	{
		return currentStage;
	}
	std::string getMapFilepath() {
		return std::string("media/map/") + std::to_string(currentStage) + std::string("/") + std::to_string(currentStage) + std::string(".map");
	}

		void win(int money);		//勝った時の獲得処理
	void lose(int money);	//負けた時の獲得処理
	
private:
	CProgressData();

	int currentStage;
	int maxStage;
	int lastStage;

	int Money;

	friend class Singleton<CProgressData>;
};