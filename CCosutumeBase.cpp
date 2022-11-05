#include "CCosutumeBase.h"
#include "CImageManager.h"
#include "CMover_Player.h"

CCostumeBase::CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate,
	int strongshotDuration, double maxSpeed, double accel, CAttribute attrDEF, std::string GID)
:animSpeed(animSpeed), MaxCharge(MaxCharge), ShotRate(ShotRate), StrongShotDuration(strongshotDuration), 
MaxSpeed(maxSpeed), Accelaration(accel), AttributeDEF(attrDEF), p_player(nullptr), GID(GID)
{
	GraphFilePath = filepath;
	CImageManager::getIns().set("player_komuk", std::make_shared<CImage>(GraphFilePath, 16, 4, 4, 32, 32));
}

void CCostumeBase::RegisterShot(std::shared_ptr<CMover_ShotBase> s)
{
	p_player->RegisterShot(s);
}
