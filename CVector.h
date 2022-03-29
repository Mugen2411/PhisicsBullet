#pragma once
#include <cmath>

const double PI = 3.141592653589;

class CVector
{
public:
	CVector();
	CVector(double, double);
	CVector(double);
	CVector(int, int);
	CVector(bool);

	double x, y;
	bool is_valid = true;	//true:—LŒø, false:–³Œø

	CVector operator +(CVector const v)const;
	CVector operator -(CVector const v)const;
	CVector operator +=(CVector const v);
	CVector operator -=(CVector const v);
	CVector operator -()const;
	CVector operator *(double const v)const;
	CVector operator /(double const v)const;
	CVector operator *=(double const v);
	bool operator !()const;
	bool operator <(CVector v)const;

	double dot(CVector const v)const;
	double cross(CVector const v)const;
	double getLength2()const;
	double getLength()const;
	double getAngle()const;
	int getDirection();
	CVector getNorm()const;

	void zero();
};

