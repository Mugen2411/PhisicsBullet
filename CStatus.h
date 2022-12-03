#pragma once
#include <cmath>

class CStatus
{
public:
	int Level;
	double ATK;
	double HP;
	double MaxHP;
	double atkCF;
	double hpCF;

	CStatus(int Level);
	CStatus(int Level, int ATK, int HP);
	CStatus(int Level, double atkCF, double hpCF);

	void Calculate();
	static int getMoneyToUpgrade(int now) {
		return 100 * std::powl(1.15, now);
	}
	CStatus Test(int TargetLevel);
	CStatus operator -(CStatus v);
};

