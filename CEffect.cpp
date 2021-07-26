#include "CEffect.h"

CEffect::CEffect(CVector pos):Position(pos),Status(0)
{
}

bool CEffect::operator!()
{
    return Status;
}
