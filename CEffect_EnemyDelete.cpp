#include "CEffect_EnemyDelete.h"
#include "CImageManager.h"

CEffect_EnemyDelete::CEffect_EnemyDelete(CVector position, double size, int color, int duration)
	:CEffect(position), Size(size), Color(color), cnt(0), animCount(0.0), duration(duration) {
}

void CEffect_EnemyDelete::Update()
{
	animCount += 8.0 / duration;
	cnt++;
	if (cnt > duration)Status = 1;
}

void CEffect_EnemyDelete::Render()const
{
	CImageManager::getIns().find("effect_bulletdelete")->DrawRotaFwithBlend(Position.x, Position.y, 0, (Size*(1-std::powl(1-(double)cnt/duration, 2)))/16.0, Color, CImageManager::BM_NONE, 255, Constant::priority_effect, animCount);
	CImageManager::getIns().find("effect_bulletdelete")->DrawRotaFwithBlend(Position.x, Position.y, 0, (Size * (1 - std::powl(1 - (double)cnt / duration, 2))) /16.0, 0xFFFFFF, CImageManager::BM_ADD, 255, Constant::priority_effect+1, animCount);
}
