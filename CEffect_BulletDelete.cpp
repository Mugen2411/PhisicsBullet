#include "CEffect_BulletDelete.h"
#include "CImageManager.h"

CEffect_BulletDelete::CEffect_BulletDelete(CVector position, CVector velocity, double size, int color)
:CEffect(position), Velocity(velocity*0.5), Size(size), Color(color), cnt(0){
}

void CEffect_BulletDelete::Update()
{
	Position += Velocity;
	cnt++;
	if (cnt / 2.0 > 7)Status = 1;
}

void CEffect_BulletDelete::Render()const
{
	CImageManager::getIns().find("effect_bulletdelete")->DrawRotaFwithBlend(Position.x, Position.y, Velocity.getAngle(), (Size*1.08) / 16.0, Color, CImageManager::BM_NONE, 255, 0.1, cnt / 2.0);
	CImageManager::getIns().find("effect_bulletdelete")->DrawRotaFwithBlend(Position.x, Position.y, Velocity.getAngle(), Size / 16.0, 0xFFFFFF, CImageManager::BM_ADD, 255, 0.1, cnt / 2.0);
}
