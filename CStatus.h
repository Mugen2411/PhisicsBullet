#pragma once
class CStatus
{
public:
	int Level;
	double ATK;
	double DEF;
	double HP;
	int MaxHP;

	CStatus(int Level);
	CStatus(int Level, int ATK, int DEF, int HP);

	void Calculate();
	CStatus Test(int TargetLevel);
	CStatus operator -(CStatus v);
};

