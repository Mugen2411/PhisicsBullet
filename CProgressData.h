#pragma once
#include "Singleton.h"
#include <algorithm>
#include <string>
#include <list>
#include <random>
#include <DxLib.h>

class CProgressData : public Singleton<CProgressData> {
public:

	void save();
	void load();

	void setCurrentStage(int stage) {	//次に入るステージ(Mediatorから設定)
		currentStage = (std::min)(stage, maxStage);
	}
	void nextCurrentStage() {	//次に入るステージ(Mediatorから設定)
		if (!isEndless)currentStage = (std::min)(++currentStage, maxStage);
		else currentStage = ++currentStage;
	}
	int getLastStage()		//今までに進んだ最大のステージ
	{
		return data.lastStage;
	}

	int getCurrentStage()	//次に入るステージ(Mediatorから参照)
	{
		return currentStage;
	}
	int getMaxStage() {
		return maxStage;
	}

	std::string getMapFilepath() {
		int cur = currentStage;
		if (isEndless) {
			if (randomStage.empty()) {
				do {
					shuffleStage();
				} while (randomStage.front() == beforeStage);
			}
			cur = randomStage.front();
			randomStage.pop_front();
			beforeStage = cur;
		}
		return std::string("media/map/") + std::to_string(cur%maxStage) + std::string("/") + std::to_string(cur%maxStage) + std::string(".map");
	}

	int getPlayerLevel() {
		return data.playerLevel;
	}

	int getMoney() {
		return data.Money;
	}

	void setWindowX2(int v) {	//0:拡大無し 1:2倍拡大
		data.isWindowX2 = v;
	}

	int getWindowX2() {
		return data.isWindowX2;
	}

	void setEndless(bool flag) {
		isEndless = flag;
	}

	bool getEndless() {
		return isEndless;
	}

	void upgrade(int money) {
		data.Money -= money;
		data.playerLevel++;
	}

	void degrade() {
		data.playerLevel--;
	}

	void win(int money);		//勝った時の獲得処理
	void lose(int money);		//負けた時の獲得処理
	void retire(int money);		//諦めた時の獲得処理

	int getEarnedMoney() {
		return earnedMoney;
	}
	int getStageMoney() {
		return stageMoney;
	}

private:
	CProgressData();

	int currentStage;
	int maxStage;
	int earnedMoney;
	int stageMoney;
	int beforeStage;

	std::list<int> randomStage;
	std::random_device dev;
	std::mt19937 eng;

	bool isEndless;

	struct progressData {
		int lastStage;		//10をかけると始めるべきステージになる
		int Money;
		int playerLevel;
		int isWindowX2;
	}data;

	void shuffleStage() {
		randomStage.clear();
		for (int i = 0; i < maxStage; i++) {
			randomStage.push_front(i);
		}
		randomStage.sort([&](int l, int r) {return eng() % 2; });
		//std::shuffle(randomStage.begin(), randomStage.end(), eng);
	}

	friend class Singleton<CProgressData>;
};