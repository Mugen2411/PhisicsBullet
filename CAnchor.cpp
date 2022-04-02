#include "CAnchor.h"
#include "Constant.h"
#include <float.h>
#include <random>

CAnchor::CAnchor() :position(0, 0), isAbsolute(false), ScrollLimit(DBL_MAX, DBL_MAX),
	diff_explosion(0, 0), explode_duration(0),isExplode(true)
{
	std::srand(1);
}

void CAnchor::setPosition(CVector newPos)
{
	position = newPos;
	position.x = fmax(0, position.x);
	position.y = fmax(0, position.y);
	position.x = fmin(ScrollLimit.x - Constant::ScreenW, position.x);
	position.y = fmin(ScrollLimit.y - Constant::ScreenH, position.y);
}

void CAnchor::setScrollLimit(CVector mapSize)
{
	ScrollLimit = mapSize * 32 + CVector(0, 0);
}

CVector CAnchor::getAnchoredPosition(CVector pos)
{
	if (isAbsolute)return pos;
	return pos - position;
}

CVector CAnchor::getWorldPosition(CVector pos)
{
	return pos + position;
}

double CAnchor::getAnchorX()
{
	if (isAbsolute)return 0.0;
	if(isExplode && explode_duration > 0)return position.x + diff_explosion.x;
	return position.x;
}

double CAnchor::getAnchorY()
{
	if (isAbsolute)return 0.0;
	if(isExplode && explode_duration > 0)return position.y + diff_explosion.y;
	return position.y;
}

void CAnchor::Move(CVector diff)
{
	setPosition(position + diff);
}

void CAnchor::Explosion(int duraiton)
{
	if (duraiton > explode_duration)explode_duration = duraiton;
}

void CAnchor::Update()
{
	if (explode_duration > 0)explode_duration--;
	diff_explosion.x = 4 - std::rand() % 8;
	diff_explosion.y = 4 - std::rand() % 8;
}

void CAnchor::enableAbsolute()
{
	isAbsolute = true;
}

void CAnchor::disableAbsolute()
{
	isAbsolute = false;
}
