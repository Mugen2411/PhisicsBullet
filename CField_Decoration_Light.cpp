#include "CField_Decoration_Light.h"
#include "CEffect_Bright.h"
#include <DxLib.h>

CField_Decoration_Light::CField_Decoration_Light(std::string gid, CVector position)
	:CField_Wall(gid, position, COF().setFrictionCF(0.6)), state(0)
{
}

void CField_Decoration_Light::Update()
{
	if (state == 0)Damage = CAttribute(0.0).THUNDER(4.0);
	else Damage = CAttribute(0.0);
	isWall = false;
}

void CField_Decoration_Light::Render() const
{
	if (state == 1) {
		CEffect_Bright::getIns().Register(CEffect_Bright::BrightDesc(Position, 512 - GetRand(16), 216));
	}
	CImageManager::getIns().find("Field_Cave")->DrawRota(Position.x, Position.y, 0.0, 1.0, Constant::priority_decoration, 5);
}

CField* CField_Decoration_Light::Clone(CVector position)
{
	return new CField_Decoration_Light(GID, position);
}
