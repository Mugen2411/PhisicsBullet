#include "CField_Decoration_Torch.h"
#include "CEffect_Bright.h"
#include <DxLib.h>

CField_Decoration_Torch::CField_Decoration_Torch(std::string gid, CVector position)
	:CField_Wall(gid, position, COF().setFrictionCF(0.9)), animCount(0.0), state(0), BurningTime(600)
{
}

void CField_Decoration_Torch::Update()
{
	animCount += 0.15;
	animCount = std::fmod(animCount, 3);
	BurningTime--;
	if (state == 1)Damage = CAttribute(0.0).FIRE(4.0);
	else Damage = CAttribute(0.0);
	isWall = false;
}

void CField_Decoration_Torch::Render() const
{
	if (state == 1) {
		CEffect_Bright::getIns().Register(CEffect_Bright::BrightDesc(Position, 512 - GetRand(16), 216));
		CImageManager::getIns().find("effect_bornfire")->
			DrawRotaFwithBlend(Position.x, Position.y, GetRand(16) / 256.0f, 1.0,
				0xFFFFFF, CImageManager::BM_ADD, 216, Constant::priority_effect, animCount);
	}
	CImageManager::getIns().find("Field_Cave")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_decoration, 4);
}

CField* CField_Decoration_Torch::Clone(CVector position)
{
	return new CField_Decoration_Torch(GID, position);
}
