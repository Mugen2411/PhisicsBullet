#pragma once
#include <cmath>
#include "Constant.h"

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

	inline CVector operator +(CVector const v)const {
		return CVector(this->x + v.x, this->y + v.y);
	}
	inline CVector operator -(CVector const v)const {
		return CVector(this->x - v.x, this->y - v.y);
	}
	inline CVector operator +=(CVector const v) {
		this->x += v.x;
		this->y += v.y;
		return *this;
	}
	inline CVector operator -=(CVector const v) {
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}
	inline CVector operator -()const {
		return CVector(-x, -y);
	}
	inline CVector operator *(double const v)const {
		return CVector(this->x * v, this->y * v);
	}
	inline CVector operator /(double const v)const {
		return CVector(this->x / v, this->y / v);
	}
	inline CVector operator *=(double const v) {
		*this = *this * v;
		return *this;
	}
	inline bool operator !()const {
		return !is_valid;
	}
	inline bool operator <(CVector v)const {
		if (x == v.x) {
			if (y < v.y)return true;
			else return false;
		}
		else {
			if (x < v.x)return true;
			else return false;
		}
	}

	inline double dot(CVector const v)const {
		return this->x * v.x + this->y * v.y;
	}
	inline double cross(CVector const v)const {
		return v.x * y - v.y * x;
	}
	inline double getLength2()const {
		return x * x + y * y;
	}
	inline double getLength()const {
		return sqrt(getLength2());
	}
	inline double getAngle()const {
		return atan2(y, x);
	}
	int getDirection();
	CVector getNorm()const;

	inline void zero() {
		if (getLength2() < Constant::zero_border) {
			x *= 0.0001;
			y *= 0.0001;
		}
	}
};