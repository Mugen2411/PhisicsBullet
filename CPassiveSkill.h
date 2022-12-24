#pragma once
#include "Singleton.h"
#include "CAttribute.h"
#include "CTextDrawer.h"
#include <set>
#include <random>
#include <algorithm>

class CPassiveSkill :public Singleton<CPassiveSkill> {
public:
	CAttribute getATKmult();
	CAttribute getDEFmult();
	double getHealRatio() {
		return 0.01 * healPerLEVEL * has[HEAL];
	}
	double getMoneyMult() {
		return 1.0 + 0.01 * moneyPerLEVEL * has[MONEY];
	}
	double getChargeMult() {
		return 1.0 + 0.01 * chargePerLEVEL * has[CHARGE];
	}
	double getSpeedMult() {
		return 1.0 + 0.01 * speedPerLEVEL * has[SPEED];
	}
	void Reset() {
		for (auto& i : has) {
			i = 0;
		}
	}

	std::vector<int> getRandomList();

	std::vector<int> getGotSkillList() {
		std::vector<int> ret;
		for (int i = 0; i < 20; i++) {
			if (has[i] != 0)ret.push_back(i);
		}
		return ret;
	}
	std::vector<int> getGotSkillLevelList() {
		std::vector<int> ret;
		for (int i = 0; i < 20; i++) {
			if (has[i] != 0)ret.push_back(has[i]);
		}
		return ret;
	}

	void add(int index) {
		has[index] = (std::min)(++has[index], 5);
	}

	CTextDrawer::Text getText(int index);
protected:
	int has[7 + 7 + 2 + 4];
	enum {
		ATK_NONE, ATK_FIRE, ATK_AQUA, ATK_THUNDER, ATK_FLOWER, ATK_ICE, ATK_WIND,
		DEF_NONE, DEF_FIRE, DEF_AQUA, DEF_THUNDER, DEF_FLOWER, DEF_ICE, DEF_WIND,
		ATK_ALL, DEF_ALL, HEAL, MONEY, CHARGE, SPEED
	};
	const int attrATKperLEVEL = 10;
	const int attrDEFperLEVEL = 10;
	const int allATKperLEVEL = 5;
	const int allDEFperLEVEL = 5;
	const double healPerLEVEL = 0.5;
	const int moneyPerLEVEL = 10;
	const int chargePerLEVEL = 2;
	const int speedPerLEVEL = 2;

	std::random_device rnd;
	std::mt19937 engine;
	CPassiveSkill();
	friend Singleton<CPassiveSkill>;
};