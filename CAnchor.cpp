#include "CAnchor.h"
#include "Constant.h"
#include <float.h>
#include <random>

CAnchor::CAnchor() :position(0, 0), isAbsolute(false), ScrollLimit(DBL_MAX, DBL_MAX),
	diff_quake(0, 0), quake_duration(0),isExplode(true)
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

void CAnchor::Update()
{
	if (quake_duration > 0)quake_duration--;
	diff_quake.x = 4 - std::rand() % 8;
	diff_quake.y = 4 - std::rand() % 8;
}