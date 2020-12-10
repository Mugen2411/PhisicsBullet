#include "CVector.h"
#include "Constant.h"

CVector::CVector(double x, double y) :x(x), y(y)
{
}

CVector CVector::operator+(const CVector v)
{
	return CVector(this->x + v.x, this->y + v.y);
}

CVector CVector::operator-(const CVector v)
{
	return CVector(this->x - v.x, this->y - v.y);
}

CVector CVector::operator+=(CVector const v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

CVector CVector::operator-=(CVector const v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

CVector CVector::operator-()
{
	return CVector(-x, -y);
}

CVector CVector::operator*(double const v)
{
	return CVector(this->x * v, this->y * v);
}

CVector CVector::operator/(double const v)
{
	return CVector(this->x / v, this->y / v);
}

double CVector::dot(CVector const v)
{
	return this->x * v.x + this->y * v.y;
}

double CVector::getLength2()
{
	return x * x + y * y;
}

CVector CVector::getNorm()
{
	double l = sqrt(getLength2());
	if (l == 0.0)return CVector(0.0, 0.0);
	return *this / l;
}

void CVector::zero()
{
	if (getLength2() < Constant::zero_border) {
		x = 0;
		y = 0;
	}
}
