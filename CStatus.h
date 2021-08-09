#pragma once
class CStatus
{
public:
	int Level;
	int ATK;
	int DEF;
	int HP;

	CStatus(int Level);
	CStatus(int Level, int ATK, int DEF, int HP);

	void Update();
	CStatus Test(int TargetLevel);
	CStatus operator -(CStatus v);
};

