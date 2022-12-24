#pragma once
#include "Singleton.h"
#include "CAttribute.h"
#include <set>

class CPassiveSkill :public Singleton<CPassiveSkill> {
public:
	CAttribute getATKmult();
	CAttribute getDEFmult();
	double getHealRatio() {
		return 0.005 * has[HEAL];
	}
	double getMoneyRatio() {
		return 1.0 + 0.05 * has[MONEY];
	}
	double getChargeMult() {
		return 1.0 + 0.02 * has[CHARGE];
	}
	double getSpeedMult() {
		return 1.0 + 0.02 * has[SPEED];
	}
	void Reset() {
		for (auto& i : has) {
			i = 0;
		}
	}
	std::set<int> getRandomList() {
		std::set<int> ret;
		int idx = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 5 - has[i]; j++) {
				ret.insert(i);
			}
		}
		return ret;
	}

	std::set<int> getRandomList(int got[5]) {
		std::set<int> ret;
		int p = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 5; j++) {
				p |= got[j] == i;
			}
			if (!p)continue;
			for (int j = 0; j < 5 - has[i]; j++) {
				ret.insert(i);
			}
		}
		return ret;
	}

	void add(int index) {
		has[index] = std::min(++has[index], 5);
	}
protected:
	int has[7 + 7 + 2 + 4];
	enum {
		ATK_NONE, ATK_FIRE, ATK_AQUA, ATK_THUNDER, ATK_FLOWER, ATK_ICE, ATK_WIND,
		DEF_NONE, DEF_FIRE, DEF_AQUA, DEF_THUNDER, DEF_FLOWER, DEF_ICE, DEF_WIND,
		ATK_ALL, DEF_ALL, HEAL, MONEY, CHARGE, SPEED
	};
	CPassiveSkill();
	friend Singleton<CPassiveSkill>;
};