#pragma once
class CAttribute
{
public:
	double None;
	double Fire;
	double Aqua;
	double Thunder;
	double Flower;
	double Ice;

	CAttribute operator *(CAttribute a);
	CAttribute operator *(double a);
	CAttribute operator +(CAttribute a);
	CAttribute operator -(CAttribute a);
};

