#include "CMover.h"

CMover::CMover(CVector position, double size, CVector velocity, double mass, double sfrictionCF, double frictionCF, double airresCF, double reflectCF, double temperature)
	:med(nullptr), Position(position), Velocity(velocity), Acceleration(0.0, 0.0), Size(size * 0.5),
	Mass(mass), SFrictionCF(sfrictionCF), FrictionCF(frictionCF), AirResCF(airresCF),
	ReflectCF(reflectCF), Temperature(temperature), Status(0)
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

void CMover::ApplyForce(CVector F)
{
	Acceleration += (F / Mass);
}

CVector CMover::getFrictionForce(double FloorFrictionCF)
{
	auto NormA = Velocity.getNorm();
	return -NormA * FrictionCF * FloorFrictionCF * Mass * Constant::Gravity;
}

void CMover::Move()
{
	Velocity += Acceleration * Constant::perFrame;
	Position += Velocity;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Velocity.zero();
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
		if(Acceleration.y < 0)Acceleration.y = 0;
	}
	if (D) {
		Position.y = WallPosition.y - WallSize.y / 2 - Size;
		Velocity.y *= -ReflectCF * WallReflectionCF;
		if (Acceleration.y > 0)Acceleration.y = 0;
	}
	if (R) {
		Position.x = WallPosition.x - WallSize.x / 2 - Size;
		Velocity.x *= -ReflectCF * WallReflectionCF;
		if (Acceleration.x > 0)Acceleration.x = 0;
	}
	if (L) {
		Position.x = WallPosition.x + WallSize.x / 2 + Size;
		Velocity.x *= -ReflectCF * WallReflectionCF;
		if (Acceleration.x < 0)Acceleration.x = 0;
	}
}
