#pragma once
#include "Singleton.h"
#include <algorithm>
#include <string>

class CProgressData : public Singleton<CProgressData> {
public:

	void save();
	void load();

	void setCurrentStage(int stage) {	//���ɓ���X�e�[�W(Mediator����ݒ�)
		currentStage = (std::min)(stage, maxStage);
	}
	void nextCurrentStage() {	//���ɓ���X�e�[�W(Mediator����ݒ�)
		currentStage = (std::min)(++currentStage, maxStage);
	}
	int getLastStage()		//���܂łɐi�񂾍ő�̃X�e�[�W
	{
		return data.lastStage;
	}

	int getCurrentStage()	//���ɓ���X�e�[�W(Mediator����Q��)
	{
		return currentStage;
	}
	std::string getMapFilepath() {
		return std::string("media/map/") + std::to_string(currentStage) + std::string("/") + std::to_string(currentStage) + std::string(".map");
	}

	int getPlayerLevel() {
		return data.playerLevel;
	}

	int getMoney() {
		return data.Money;
	}

	void upgrade(int money) {
		data.Money -= money;
		data.playerLevel++;
	}

	void win(int money);		//���������̊l������
	void lose(int money);		//���������̊l������
	void retire(int money);		//���߂����̊l������

	int getEarnedMoney() {
		return earnedMoney;
	}

private:
	CProgressData();

	int currentStage;
	int maxStage;
	int earnedMoney;

	struct progressData {
		int lastStage;		//10��������Ǝn�߂�ׂ��X�e�[�W�ɂȂ�
		int Money;
		int playerLevel;
	}data;

	friend class Singleton<CProgressData>;
};