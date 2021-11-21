#include "CStatus.h"
#include <cmath>

CStatus::CStatus(int Level) :atkCF(1.0), defCF(1.0), hpCF(1.0)
{
	this->Level = Level;
	Calculate();
}

CStatus::CStatus(int Level, int ATK, int DEF, int HP)
	:Level(Level), ATK(ATK), DEF(DEF), HP(HP), MaxHP(HP)
	, atkCF(1.0), defCF(1.0), hpCF(1.0)
{
}

CStatus::CStatus(int Level, double atkCF, double defCF, double hpCF)
	: atkCF(atkCF), defCF(defCF), hpCF(hpCF)
{
	this->Level = Level;
	Calculate();
}

void CStatus::Calculate()
{
	ATK = (100 * std::pow(1.08, Level) + 2 * Level) * atkCF;
	DEF = (100 * std::pow(1.05, Level) + 2 * Level) * defCF;
	MaxHP = (1000 * std::pow(1.03, Level) + 5 * Level) * hpCF;
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
