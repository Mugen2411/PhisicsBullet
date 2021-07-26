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
