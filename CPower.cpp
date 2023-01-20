#include "CPower.h"

CPower::CPower(CVector position, double power, int duration)
	:parent(nullptr), Position(position), Power(power), duration(duration), cnt(0)
{
}
