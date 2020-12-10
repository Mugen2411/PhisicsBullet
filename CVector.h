#pragma once
#include <math.h>

class CVector
{
public:
	CVector(double, double);

	double x, y;

	CVector operator +(CVector const v);
	CVector operator -(CVector const v);
	CVector operator +=(CVector const v);
	CVector operator -=(CVector const v);
	CVector operator -();
	CVector operator *(double const v);
	CVector operator /(double const v);

	double dot(CVector const v);
	double getLength2();
	CVector getNorm();

	void zero();
};

