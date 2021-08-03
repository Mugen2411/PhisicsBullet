#include "CMover_BulletBase.h"
#include "CImageManager.h"
#include <DxLib.h>

CMover_BulletBase::CMover_BulletBase(CVector position, double size, CVector velocity, double mass, double frictionCF, double airresCF, double reflectCF)
	:CMover(MV_BULLET, position, 16, velocity, mass, 0, frictionCF, airresCF, reflectCF, 0)
{
}