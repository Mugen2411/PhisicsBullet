#include "CStatus.h"
#include <cmath>

CStatus::CStatus(int Level)
{
	this->Level = Level;
	Calculate();
}

CStatus::CStatus(int Level, int ATK, int DEF, int HP)
	:Level(Level), ATK(ATK), DEF(DEF), HP(HP), MaxHP(HP)
{
}

void CStatus::Calculate()
{
	ATK = 100 * std::pow(1.08, Level) + 2 * Level;
	DEF = 100 * std::pow(1.05, Level) + 2 * Level;
	MaxHP = 1000 * std::pow(1.03, Level) + 5 * Level;
	HP = MaxHP;
}

CStatus CStatus::Test(int TargetLevel)
{
	CStatus test(TargetLevel);
	return test - (*this);
}

CStatus CStatus::operator-(CStatus v)
{
	return CStatus(Level - v.Level, ATK - v.ATK, DEF - v.DEF, HP - v.HP);
}
