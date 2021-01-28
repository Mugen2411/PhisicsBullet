#pragma once
#include <math.h>

class CVector
{
public:
	CVector();
	CVector(double, double);
	CVector(double);

	double x, y;

	CVector operator +(CVector const v)const;
	CVector operator -(CVector const v)const;
	CVector operator +=(CVector const v);
	CVector operator -=(CVector const v);
	CVector operator -()const;
	CVector operator *(double const v)const;
	CVector operator /(double const v)const;

	double dot(CVector const v)const;
	double cross(CVector const v)const;
	double getLength2()const;
	double getLength()const;
	double getAngle()const;
	CVector getNorm()const;

	void zero();
};

