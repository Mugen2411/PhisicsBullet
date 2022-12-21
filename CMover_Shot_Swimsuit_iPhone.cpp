#include "CMover_Shot_Swimsuit_iPhone.h"
#include "CImageManager.h"
#include "CSoundManager.h"
#include "CEffectParent.h"
#include "CEffect_BulletDelete.h"

CMover_Shot_Swimsuit_iPhone::CMover_Shot_Swimsuit_iPhone(double baseATK, CVector position, double angle)
	:CMover_ShotBase(baseATK, CAttribute(0.0).NONE(10).THUNDER(50), position, 24, CVector(angle) * 16.0, 2.0, COF(0.02, 0.05, 0.05, 0.1), 0x7F7F7F),
	renderAngle(0.0)
{
}

void CMover_Shot_Swimsuit_iPhone::Dead()
{
	CEffectParent::RegisterEffect(std::make_shared<CEffect_BulletDelete>(Position, Velocity, Size, effectColor));
	CSoundManager::getIns().find("glassBreak")->Play(CSound::PLAYTYPE::PT_BACK);
}

int CMover_Shot_Swimsuit_iPhone::Update()
{
	if (Velocity.getLength2() < 0.05) {
		setStatus(STATUS::DEAD);
	}
	renderAngle += Constant::PI2 * Constant::perFrame * 1.5;
	return Status;
}

void CMover_Shot_Swimsuit_iPhone::Render() const
{
	CImageManager::getIns().find("shot_swimsuit_iphone")->DrawRotaF(Position.x, Position.y, Velocity.getAngle()+renderAngle, 1, Constant::priority_shot);
}
