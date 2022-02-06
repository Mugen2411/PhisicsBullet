#include "CAnchor.h"
#include "Constant.h"
#include <float.h>

CAnchor::CAnchor() :position(0, 0), isAbsolute(false), ScrollLimit(DBL_MAX, DBL_MAX)
{
}

void CAnchor::setPosition(CVector newPos)
{
	//position = newPos;
	position.x = fmin(ScrollLimit.x - Constant::ScreenW, newPos.x);
	position.y = fmin(ScrollLimit.y - Constant::ScreenH, newPos.y);
	position.x = fmax(0, position.x);
	position.y = fmax(0, position.y);
}

void CAnchor::setScrollLimit(CVector mapSize)
{
	ScrollLimit = mapSize * 32;
}

CVector CAnchor::getAnchoredPosition(CVector pos)
{
	if (isAbsolute)return pos;
	return pos - position;
}

CVector CAnchor::getWorldPosition(CVector pos)
{
	return pos + position;;
}

double CAnchor::getAnchorX()
{
	if (isAbsolute)return 0.0;
	return position.x;
}

double CAnchor::getAnchorY()
{
	if (isAbsolute)return 0.0;
	return position.y;
}

void CAnchor::enableAbsolute()
{
	isAbsolute = true;
}

void CAnchor::disableAbsolute()
{
	isAbsolute = false;
}
