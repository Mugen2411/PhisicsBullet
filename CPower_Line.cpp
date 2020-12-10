#include "CPower_Line.h"

CPower_Line::CPower_Line(CPowerParent* p, CVector position, CVector direction, double width)
	:CPower(p), Position(position), Direction(direction), Width(width)
{
}
