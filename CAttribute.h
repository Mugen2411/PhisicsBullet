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

	CAttribute();
	CAttribute(double none, double fire, double aqua, double thunder, double flower, double ice);

	CAttribute operator *(CAttribute a);
	CAttribute operator *(double a);
	CAttribute operator +(CAttribute a);
	CAttribute operator -(CAttribute a);
	double Sum();
};

