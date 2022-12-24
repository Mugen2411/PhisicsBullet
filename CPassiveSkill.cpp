#include "CPassiveSkill.h"

CAttribute CPassiveSkill::getATKmult()
{
	CAttribute ret(1.0);
	ret.None *= 1.0 + 0.03 * has[ATK_NONE];
	ret.Fire *= 1.0 + 0.03 * has[ATK_FIRE];
	ret.Aqua *= 1.0 + 0.03 * has[ATK_AQUA];
	ret.Thunder *= 1.0 + 0.03 * has[ATK_THUNDER];
	ret.Flower *= 1.0 + 0.03 * has[ATK_FLOWER];
	ret.Ice *= 1.0 + 0.03 * has[ATK_ICE];
	ret.Wind *= 1.0 + 0.03 * has[ATK_WIND];
	ret *= CAttribute(1.0 + 0.01 * has[ATK_ALL]);
	return ret;
}

CAttribute CPassiveSkill::getDEFmult()
{
	CAttribute ret(1.0);
	ret.None *= 1.0 + 0.03 * has[DEF_NONE];
	ret.Fire *= 1.0 + 0.03 * has[DEF_FIRE];
	ret.Aqua *= 1.0 + 0.03 * has[DEF_AQUA];
	ret.Thunder *= 1.0 + 0.03 * has[DEF_THUNDER];
	ret.Flower *= 1.0 + 0.03 * has[DEF_FLOWER];
	ret.Ice *= 1.0 + 0.03 * has[DEF_ICE];
	ret.Wind *= 1.0 + 0.03 * has[DEF_WIND];
	ret *= CAttribute(1.0 + 0.01 * has[DEF_ALL]);
	return ret;
}

CPassiveSkill::CPassiveSkill(): has{0}
{
}
