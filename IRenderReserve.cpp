#include "IRenderReserve.h"

IRenderReserve::IRenderReserve(int GHandle, double Priority)
	:GHandle(GHandle),Priority(Priority)
{
}

bool IRenderReserve::operator<(IRenderReserve *rhs)
{
	return Priority < rhs->Priority;
}

bool compRenderReserve(IRenderReserve* l, IRenderReserve* r) {
	return l->Priority < r->Priority;
}
