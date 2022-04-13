#pragma once
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
	CStatus Test(int TargetLevel);
	CStatus operator -(CStatus v);
};

