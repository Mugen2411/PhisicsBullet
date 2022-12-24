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
		if (!isEndless)currentStage = (std::min)(++currentStage, maxStage);
		else currentStage = ++currentStage;
	}
	int getLastStage()		//���܂łɐi�񂾍ő�̃X�e�[�W
	{
		return data.lastStage;
	}

	int getCurrentStage()	//���ɓ���X�e�[�W(Mediator����Q��)
	{
		return currentStage;
	}
	int getMaxStage() {
		return maxStage;
	}

	std::string getMapFilepath() {
		return std::string("media/map/") + std::to_string(currentStage%maxStage) + std::string("/") + std::to_string(currentStage%maxStage) + std::string(".map");
	}

	int getPlayerLevel() {
		return data.playerLevel;
	}

	int getMoney() {
		return data.Money;
	}

	void setWindowX2(int v) {	//0:�g�喳�� 1:2�{�g��
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

	void win(int money);		//���������̊l������
	void lose(int money);		//���������̊l������
	void retire(int money);		//���߂����̊l������

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

	bool isEndless;

	struct progressData {
		int lastStage;		//10��������Ǝn�߂�ׂ��X�e�[�W�ɂȂ�
		int Money;
		int playerLevel;
		int isWindowX2;
	}data;

	friend class Singleton<CProgressData>;
};