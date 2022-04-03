#include "CVector.h"

CVector::CVector() :x(0.0), y(0.0)
{
}

CVector::CVector(double x, double y) :x(x), y(y)
{
}

CVector::CVector(double angle): x(cos(angle)), y(sin(angle))
{
}

CVector::CVector(int x, int y): x(x), y(y)
{
}

CVector::CVector(bool v):x(0),y(0) {
	is_valid = false;
}

int CVector::getDirection()
{
	double angle = getAngle();
	angle = std::fmod(angle + PI*2, PI * 2);
	if (PI / 4.0 * 5.0 < angle && angle <= PI / 4.0 * 7.0)return 2;
	if (PI / 4.0 * 3.0 < angle && angle <= PI / 4.0 * 5.0)return 1;
	if (PI / 4.0 < angle && angle <= PI / 4.0 * 3.0)return 0;
	return 3;
}

CVector CVector::getNorm()const
{
	double l = sqrt(getLength2());
	if (l == 0.0)return CVector(0.0, 0.0);
	return *this / l;
}