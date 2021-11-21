#pragma once
class CStatus
{
public:
	int Level;
	double ATK;
	double DEF;
	double HP;
	int MaxHP;
	double atkCF;
	double defCF;
	double hpCF;

	CStatus(int Level);
	CStatus(int Level, int ATK, int DEF, int HP);
	CStatus(int Level, double atkCF, double defCF, double hpCF);

	void Calculate();
	CStatus Test(int TargetLevel);
	CStatus operator -(CStatus v);
};

