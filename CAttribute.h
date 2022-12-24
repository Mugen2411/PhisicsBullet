#pragma once
#include "Constant.h"

class CAttribute
{
public:
	CAttribute(double init);

	CAttribute NONE(double value);
	CAttribute FIRE(double value);
	CAttribute AQUA(double value);
	CAttribute THUNDER(double value);
	CAttribute FLOWER(double value);
	CAttribute ICE(double value);
	CAttribute WIND(double value);

	double None;
	double Fire;
	double Aqua;
	double Thunder;
	double Flower;
	double Ice;
	double Wind;

	CAttribute operator *(CAttribute a);
	CAttribute operator *(double a);
	CAttribute operator *=(CAttribute a);
	CAttribute operator /(CAttribute a);
	CAttribute operator /(double a);
	CAttribute operator +(CAttribute a);
	CAttribute operator +=(CAttribute a);
	CAttribute operator -(CAttribute a);
	bool isZero();
	double Sum();
};

