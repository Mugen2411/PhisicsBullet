#include "CAttribute.h"
#include <cmath>

CAttribute CAttribute::operator*(double a)
{
	CAttribute ret(0.0);
	ret.None = this->None * a;
	ret.Fire = this->Fire * a;
	ret.Aqua = this->Aqua * a;
	ret.Thunder = this->Thunder * a;
	ret.Flower = this->Flower * a;
	ret.Ice = this->Ice * a;
	return ret;
}

CAttribute CAttribute::operator*=(CAttribute a)
{
	CAttribute ret = *this * a;
	*this = ret;
	return ret;
}

CAttribute CAttribute::operator/(double a)
{
	a = 1.0 / a;
	CAttribute ret(0.0);
	ret = *this * a;
	return ret;
}

CAttribute::CAttribute(double init)
:None(init), Fire(init), Aqua(init), Thunder(init), Flower(init), Ice(init){
}

CAttribute CAttribute::NONE(double value)
{
	this->None = value;
	return *this;
}

CAttribute CAttribute::FIRE(double value)
{	
	this->Fire = value;
	return *this;
}

CAttribute CAttribute::AQUA(double value)
{
	this->Aqua = value;
	return *this;
}

CAttribute CAttribute::THUNDER(double value)
{
	this->Thunder = value;
	return *this;
}

CAttribute CAttribute::FLOWER(double value)
{
	this->Flower = value;
	return *this;
}

CAttribute CAttribute::ICE(double value)
{
	this->Ice = value;
	return *this;
}

CAttribute CAttribute::operator*(CAttribute a)
{
	CAttribute ret(0.0);
	ret.None = this->None * a.None;
	ret.Fire = this->Fire * a.Fire;
	ret.Aqua = this->Aqua * a.Aqua;
	ret.Thunder = this->Thunder * a.Thunder;
	ret.Flower = this->Flower * a.Flower;
	ret.Ice = this->Ice * a.Ice;
	return ret;
}

CAttribute CAttribute::operator/(CAttribute a)
{
	CAttribute ret(0.0);
	ret.None = this->None / a.None;
	ret.Fire = this->Fire / a.Fire;
	ret.Aqua = this->Aqua / a.Aqua;
	ret.Thunder = this->Thunder / a.Thunder;
	ret.Flower = this->Flower / a.Flower;
	ret.Ice = this->Ice / a.Ice;
	return ret;
}

CAttribute CAttribute::operator+(CAttribute a)
{
	CAttribute ret(0.0);
	ret.None = this->None + a.None;
	ret.Fire = this->Fire + a.Fire;
	ret.Aqua = this->Aqua + a.Aqua;
	ret.Thunder = this->Thunder + a.Thunder;
	ret.Flower = this->Flower + a.Flower;
	ret.Ice = this->Ice + a.Ice;
	return ret;
}

CAttribute CAttribute::operator+=(CAttribute a)
{
	CAttribute ret = *this + a;
	*this = ret;
	return ret;
}

CAttribute CAttribute::operator-(CAttribute a)
{
	return *this+(a*-1.0);
}

bool CAttribute::isZero()
{
	return Sum() < Constant::zero_border;
}

double CAttribute::Sum()
{
	return None + Fire + Aqua + Thunder + Flower + Ice;
}