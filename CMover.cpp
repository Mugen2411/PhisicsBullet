#include "CMover.h"
#include "CField.h"

CMover::CMover(MOVER_ID ID, CVector position, double size, CVector velocity, double mass,
	COF cofs, double temperature)
	:Position(position), Velocity(velocity), Acceleration(0.0, 0.0), Size(size * 0.5),
	Mass(mass), nowFricted(0.0), nowWatered(0.0), Cofs(cofs), Temperature(temperature), Status(STATUS::ALIVE), Category(ID)
{
}

void CMover::Hit(CMover* m)
{
}

void CMover::Hit(CMover_ShotBase* m)
{
}

void CMover::Hit(CMover_EnemyBase* m)
{
}

void CMover::Hit(CMover_Player*)
{
}

void CMover::Hit(CMover_BulletBase* m)
{
}

bool CMover::onWall(CField* f, double WallReflectionCF)
{
	CVector WallPosition = f->getPosition();
	CVector WallSize = f->getSize();
	CVector nextPosition = Position + Velocity + Acceleration;
	double max = (Position.x + Size) - (WallPosition.x - WallSize.x / 2), may = (Position.y + Size) - (WallPosition.y - WallSize.y / 2);
	double nax = (WallPosition.x + WallSize.x / 2) - (Position.x - Size), nay = (WallPosition.y + WallSize.y / 2) - (Position.y - Size);
	double _max = (nextPosition.x + Size) - (WallPosition.x - WallSize.x / 2), _may = (nextPosition.y + Size) - (WallPosition.y - WallSize.y / 2);
	double _nax = (WallPosition.x + WallSize.x / 2) - (nextPosition.x - Size), _nay = (WallPosition.y + WallSize.y / 2) - (nextPosition.y - Size);
	bool U = false, D = false, R = false, L = false;

	//カド同士の判定
	if (0 >= max && 0 >= may && _max > 0 && _may > 0) {
		if (_max >= _may) {
			//下にある
			D = true;
		}
		else {
			//右にある
			R = true;
		}
	}
	if (0 >= nax && 0 >= may && _nax > 0 && _may > 0) {
		if (_nax >= _may) {
			//下にある
			D = true;
		}
		else {
			//左にある
			L = true;
		}
	}
	if (0 >= max && 0 >= nay && _max > 0 && _nay > 0) {
		if (_max >= _nay) {
			//上にある
			U = true;
		}
		else {
			//右にある
			R = true;
		}
	}
	if (0 >= nax && 0 >= nay && _nax > 0 && _nay > 0) {
		if (_nax >= _nay) {
			//上にある
			U = true;
		}
		else {
			//左にある
			L = true;
		}
	}

	//上下左右の判定
	if (may > 0 && nay > 0) {
		if (_nax > 0 && (Position.x - Size) > (WallPosition.x - WallSize.x / 2)) {
			//左にある
			L = true;
		}
		if (_max > 0 && (WallPosition.x + WallSize.x / 2) > (Position.x + Size)) {
			//右にある
			R = true;
		}
	}
	if (max > 0 && nax > 0) {
		if (_nay > 0 && (Position.y - Size) > (WallPosition.y - WallSize.y / 2)) {
			//上にある
			U = true;
		}
		if (_may > 0 && (WallPosition.y + WallSize.y / 2) > (Position.y + Size)) {
			//下にある
			D = true;
		}
	}
	int add = 0;
	if (U) {
		Position.y = WallPosition.y + WallSize.y / 2 + (Size+1.0);
		Velocity.y *= -Cofs.ReflectCF * WallReflectionCF;
		//Acceleration.y *= -Cofs.ReflectCF * WallReflectionCF;
		Acceleration.y = 0;
		airForce.y *= -Cofs.ReflectCF * WallReflectionCF;
		waterForce.y *= -Cofs.ReflectCF * WallReflectionCF;
		frictionForce.y *= -Cofs.ReflectCF * WallReflectionCF;
		ifonWall();
	}
	if (D) {
		Position.y = WallPosition.y - WallSize.y / 2 - (Size + 1.0);
		Velocity.y *= -Cofs.ReflectCF * WallReflectionCF;
		//Acceleration.y *= -Cofs.ReflectCF * WallReflectionCF;
		Acceleration.y = 0;
		airForce.y *= -Cofs.ReflectCF * WallReflectionCF;
		waterForce.y *= -Cofs.ReflectCF * WallReflectionCF;
		frictionForce.y *= -Cofs.ReflectCF * WallReflectionCF;
		ifonWall();
	}
	if (R) {
		Position.x = WallPosition.x - WallSize.x / 2 - (Size + 1.0);
		Velocity.x *= -Cofs.ReflectCF * WallReflectionCF;
		//Acceleration.x *= -Cofs.ReflectCF * WallReflectionCF;
		Acceleration.x = 0;
		airForce.x *= -Cofs.ReflectCF * WallReflectionCF;
		waterForce.x *= -Cofs.ReflectCF * WallReflectionCF;
		frictionForce.x *= -Cofs.ReflectCF * WallReflectionCF;
		ifonWall();
	}
	if (L) {
		Position.x = WallPosition.x + WallSize.x / 2 + (Size + 1.0);
		Velocity.x *= -Cofs.ReflectCF * WallReflectionCF;
		//Acceleration.x *= -Cofs.ReflectCF * WallReflectionCF;
		Acceleration.x = 0;
		airForce.x *= -Cofs.ReflectCF * WallReflectionCF;
		waterForce.x *= -Cofs.ReflectCF * WallReflectionCF;
		frictionForce.x *= -Cofs.ReflectCF * WallReflectionCF;
		ifonWall();
	}
	isLockedAxis = ((U | D) << 1) | (R | L);
	return (U | D) << 1 | (R | L);
}
