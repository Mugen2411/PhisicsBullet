#include "CMover.h"

CMover::CMover(MOVER_ID ID, CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF, double temperature)
	:Position(position), Velocity(velocity), Acceleration(0.0, 0.0), Size(size * 0.5),
	Mass(mass), nowFricted(0.0), FrictionCF(frictionCF), AirResCF(airresCF),
	ReflectCF(reflectCF), Temperature(temperature), Status(0), Category(ID)
{
}

void CMover::setMediator(std::shared_ptr<CGameMediator> m)
{
	med = m;
}

CVector CMover::getPosition()
{
	return Position;
}

double CMover::getSize()
{
	return Size;
}

int CMover::getCategory()
{
	return Category;
}

void CMover::ApplyForce(CVector F)
{
	Acceleration += (F / Mass);
}

void CMover::ApplyFrictionForce(double FloorFrictionCF)
{
	nowFricted = FloorFrictionCF;
	auto NormA = Velocity.getNorm();
	ApplyForce(-NormA * FrictionCF * FloorFrictionCF * Mass * Constant::Gravity);
}

void CMover::ApplyAirForce(CVector F)
{
	ApplyForce(F * AirResCF);
}

void CMover::Move()
{
	Velocity += Acceleration * Constant::perFrame;
	Position += Velocity;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Velocity.zero();
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

void CMover::onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF)
{
	CVector nextPosition = Position + Velocity + Acceleration*Constant::perFrame;
	double max = (Position.x + Size) - (WallPosition.x - WallSize.x / 2), may = (Position.y + Size) - (WallPosition.y - WallSize.y / 2);
	double nax = (WallPosition.x + WallSize.x / 2) - (Position.x - Size), nay = (WallPosition.y + WallSize.y / 2) - (Position.y - Size);
	double _max = (nextPosition.x + Size) - (WallPosition.x - WallSize.x / 2), _may = (nextPosition.y + Size) - (WallPosition.y - WallSize.y / 2);
	double _nax = (WallPosition.x + WallSize.x / 2) - (nextPosition.x - Size), _nay = (WallPosition.y + WallSize.y / 2) - (nextPosition.y - Size);
	bool U = false, D = false, R = false, L = false;

	//�J�h���m�̔���
	if (0 >= max && 0 >= may && _max > 0 && _may > 0) {
		if (_max >= _may) {
			//���ɂ���
			D = true;
		}
		else {
			//�E�ɂ���
			R = true;
		}
	}
	if (0 >= nax && 0 >= may && _nax > 0 && _may > 0) {
		if (_nax >= _may) {
			//���ɂ���
			D = true;
		}
		else {
			//���ɂ���
			L = true;
		}
	}
	if (0 >= max && 0 >= nay && _max > 0 && _nay > 0) {
		if (_max >= _nay) {
			//��ɂ���
			U = true;
		}
		else {
			//�E�ɂ���
			R = true;
		}
	}
	if (0 >= nax && 0 >= nay && _nax > 0 && _nay > 0) {
		if (_nax >= _nay) {
			//��ɂ���
			U = true;
		}
		else {
			//���ɂ���
			L = true;
		}
	}

	//�㉺���E�̔���
	if (may > 0 && nay > 0) {
		if (_nax > 0 && (Position.x - Size) > (WallPosition.x - WallSize.x / 2)) {
			//���ɂ���
			L = true;
		}
		if (_max > 0 && (WallPosition.x + WallSize.x / 2) > (Position.x + Size)) {
			//�E�ɂ���
			R = true;
		}
	}
	if (max > 0 && nax > 0) {
		if (_nay > 0 && (Position.y - Size) > (WallPosition.y - WallSize.y / 2)) {
			//��ɂ���
			U = true;
		}
		if (_may > 0 && (WallPosition.y + WallSize.y / 2) > (Position.y + Size)) {
			//���ɂ���
			D = true;
		}
	}
	if (U) {
		Position.y = WallPosition.y + WallSize.y / 2 + Size;
		Velocity.y *= -ReflectCF * WallReflectionCF;
		Acceleration.y *= -ReflectCF * WallReflectionCF;
		//Velocity.x *= ReflectCF * WallReflectionCF;
		if(Acceleration.y < 0)Acceleration.y = 0;
		ifonWall();
	}
	if (D) {
		Position.y = WallPosition.y - WallSize.y / 2 - Size;
		Velocity.y *= -ReflectCF * WallReflectionCF;
		Acceleration.y *= -ReflectCF * WallReflectionCF;
		//Velocity.x *= ReflectCF * WallReflectionCF;
		if (Acceleration.y > 0)Acceleration.y = 0;
		ifonWall();
	}
	if (R) {
		Position.x = WallPosition.x - WallSize.x / 2 - Size;
		Velocity.x *= -ReflectCF * WallReflectionCF;
		Acceleration.x *= -ReflectCF * WallReflectionCF;
		//Velocity.y *= ReflectCF * WallReflectionCF;
		if (Acceleration.x > 0)Acceleration.x = 0;
		ifonWall();
	}
	if (L) {
		Position.x = WallPosition.x + WallSize.x / 2 + Size;
		Velocity.x *= -ReflectCF * WallReflectionCF;
		Acceleration.x *= -ReflectCF * WallReflectionCF;
		//Velocity.y *= ReflectCF * WallReflectionCF;
		if (Acceleration.x < 0)Acceleration.x = 0;
		ifonWall();
	}
}
