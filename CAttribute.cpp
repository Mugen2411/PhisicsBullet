#include "CAttribute.h"

CAttribute CAttribute::operator*(double a)
{
	CAttribute ret;
	ret.None = this->None * a;
	ret.Fire = this->Fire * a;
	ret.Aqua = this->Aqua * a;
	ret.Aqua = this->Thunder * a;
	ret.Flower = this->Ice * a;
	return ret;
}

CAttribute::CAttribute():None(0), Fire(0), Aqua(0), Thunder(0), Flower(0), Ice(0)
{
}

CAttribute::CAttribute(double none, double fire, double aqua, double thunder, double flower, double ice)
:None(none), Fire(fire), Aqua(aqua), Thunder(thunder), Flower(flower), Ice(ice){
}

CAttribute CAttribute::operator*(CAttribute a)
{
	CAttribute ret;
	ret.None = this->None * a.None;
	ret.Fire = this->Fire * a.Fire;
	ret.Aqua = this->Aqua * a.Aqua;
	ret.Aqua = this->Thunder * a.Thunder;
	ret.Flower = this->Ice * a.Ice;
	return ret;
}

CAttribute CAttribute::operator+(CAttribute a)
{
	CAttribute ret;
	ret.None = this->None + a.None;
	ret.Fire = this->Fire + a.Fire;
	ret.Aqua = this->Aqua + a.Aqua;
	ret.Aqua = this->Thunder + a.Thunder;
	ret.Flower = this->Ice + a.Ice;
	return ret;
}

CAttribute CAttribute::operator-(CAttribute a)
{
	return *this+(a*-1.0);
}
