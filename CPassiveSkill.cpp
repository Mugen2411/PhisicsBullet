#include "CPassiveSkill.h"
#include "CStatus.h"

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

std::vector<int> CPassiveSkill::getRandomList() {
	std::set<int> ret;
	std::vector<int> smp;
	int got[5];
	int p = 0;
	for (int i = 0; i < 20; i++) {
		if (has[i] != 0)p++;
	}
	if (p < 5) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 5 - has[i]; j++) {
				ret.insert(i);
			}
		}
		std::sample(ret.begin(), ret.end(), std::back_inserter(smp), 3, engine);
		return smp;
	}
	p = 0;
	for (int i = 0; i < 20; i++) {
		if (has[i] != 0) {
			got[p] = i;
			p++;
		}
	}
	p = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 5; j++) {
			p |= got[j] == i;
		}
		if (!p)continue;
		for (int j = 0; j < 5 - has[i]; j++) {
			ret.insert(i);
		}
	}
	std::sample(ret.begin(), ret.end(), std::back_inserter(smp), 3, engine);
	return smp;
}

CTextDrawer::Text CPassiveSkill::getText(int index)
{
	CTextDrawer::Text ret("", CVector(32.0, 280.0), 0xFFFFFF, 0x000000, 0);
	std::string attr[7] = { "無", "炎", "水", "雷", "花", "氷", "風" };
	if (index <= ATK_WIND) {
		ret.text = std::string("与える") + attr[index % 7] + std::string("属性ダメージを") + std::to_string(has[index] * 3) +
			std::string("%→") + std::to_string((has[index] + 1) * 3) + std::string("%増加する。");
		return ret;
	}
	if (index <= DEF_WIND) {
		ret.text = std::string("受ける") + attr[index % 7] + std::string("属性ダメージを") + std::to_string(has[index] * 3) +
			std::string("%→") + std::to_string((has[index] + 1) * 3) + std::string("%軽減する。");
		return ret;
	}
	if (index == ATK_ALL) {
		ret.text = std::string("与える") + std::string("全てのダメージを") + std::to_string(has[index] * 1) +
			std::string("%→") + std::to_string((has[index] + 1) * 1) + std::string("%増加する。");
		return ret;
	}
	if (index == DEF_ALL) {
		ret.text = std::string("受ける") + std::string("全てのダメージを") + std::to_string(has[index] * 1) +
			std::string("%→") + std::to_string((has[index] + 1) * 1) + std::string("%軽減する。");
		return ret;
	}
	if (index == HEAL) {
		ret.text = std::string("HPを毎秒") + floating_to_string(has[index] * 0.5) +
			std::string("%→") + floating_to_string((has[index] + 1) * 0.5) + std::string("%回復する。");
		return ret;
	}
	if (index == MONEY) {
		ret.text = std::string("獲得する全てのコインを") + std::to_string(has[index] * 5) +
			std::string("%→") + std::to_string((has[index] + 1) * 5) + std::string("%増加する。");
		return ret;
	}
	if (index == CHARGE) {
		ret.text = std::string("射撃のチャージ速度を") + std::to_string(has[index] * 2) +
			std::string("%→") + std::to_string((has[index] + 1) * 2) + std::string("%増加する。");
		return ret;
	}
	ret.text = std::string("自機の最高速度を") + std::to_string(has[index] * 2) +
		std::string("%→") + std::to_string((has[index] + 1) * 2) + std::string("%増加する。");
	return ret;
}

CPassiveSkill::CPassiveSkill() : has{ 0 }, rnd(), engine(rnd())
{
}
