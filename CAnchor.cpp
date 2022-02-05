#include "CAnchor.h"

CAnchor::CAnchor():position(0,0),isAbsolute(false)
{
}

void CAnchor::setPosition(CVector newPos)
{
	position = newPos;
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
