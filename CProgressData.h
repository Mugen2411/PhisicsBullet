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
	int getLastStage()		//���܂łɐi�񂾍ő�̃X�e�[�W
	{
		return lastStage;
	}

	int getCurrentStage()	//���ɓ���X�e�[�W(Mediator����Q��)
	{
		return currentStage;
	}
	std::string getMapFilepath() {
		return std::string("media/map/") + std::to_string(currentStage) + std::string("/") + std::to_string(currentStage) + std::string(".map");
	}

		void win(int money);		//���������̊l������
	void lose(int money);	//���������̊l������
	
private:
	CProgressData();

	int currentStage;
	int maxStage;
	int lastStage;

	int Money;

	friend class Singleton<CProgressData>;
};